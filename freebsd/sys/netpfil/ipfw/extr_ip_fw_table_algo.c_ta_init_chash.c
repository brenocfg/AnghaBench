#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */

/* Type definitions */
typedef  int /*<<< orphan*/  uint8_t ;
typedef  int uint32_t ;
struct table_info {int data; int /*<<< orphan*/  lookup; int /*<<< orphan*/ * xstate; int /*<<< orphan*/ * state; } ;
struct ip_fw_chain {int dummy; } ;
struct chashbhead {int dummy; } ;
struct chash_cfg {int mask4; int mask6; int size4; int size6; int /*<<< orphan*/ * head6; int /*<<< orphan*/ * head4; } ;

/* Variables and functions */
 int /*<<< orphan*/  M_IPFW ; 
 int M_WAITOK ; 
 int M_ZERO ; 
 int /*<<< orphan*/  SLIST_INIT (int /*<<< orphan*/ *) ; 
 int chash_parse_opts (struct chash_cfg*,char*) ; 
 int /*<<< orphan*/  free (struct chash_cfg*,int /*<<< orphan*/ ) ; 
 void* malloc (int,int /*<<< orphan*/ ,int) ; 
 int ta_log2 (int) ; 
 int /*<<< orphan*/  ta_lookup_chash_64 ; 
 int /*<<< orphan*/  ta_lookup_chash_aligned ; 
 int /*<<< orphan*/  ta_lookup_chash_slow ; 

__attribute__((used)) static int
ta_init_chash(struct ip_fw_chain *ch, void **ta_state, struct table_info *ti,
    char *data, uint8_t tflags)
{
	int error, i;
	uint32_t hsize;
	struct chash_cfg *cfg;

	cfg = malloc(sizeof(struct chash_cfg), M_IPFW, M_WAITOK | M_ZERO);

	cfg->mask4 = 32;
	cfg->mask6 = 128;

	if ((error = chash_parse_opts(cfg, data)) != 0) {
		free(cfg, M_IPFW);
		return (error);
	}

	cfg->size4 = 128;
	cfg->size6 = 128;

	cfg->head4 = malloc(sizeof(struct chashbhead) * cfg->size4, M_IPFW,
	    M_WAITOK | M_ZERO);
	cfg->head6 = malloc(sizeof(struct chashbhead) * cfg->size6, M_IPFW,
	    M_WAITOK | M_ZERO);
	for (i = 0; i < cfg->size4; i++)
		SLIST_INIT(&cfg->head4[i]);
	for (i = 0; i < cfg->size6; i++)
		SLIST_INIT(&cfg->head6[i]);


	*ta_state = cfg;
	ti->state = cfg->head4;
	ti->xstate = cfg->head6;

	/* Store data depending on v6 mask length */
	hsize = ta_log2(cfg->size4) << 8 | ta_log2(cfg->size6);
	if (cfg->mask6 == 64) {
		ti->data = (32 - cfg->mask4) << 24 | (128 - cfg->mask6) << 16|
		    hsize;
		ti->lookup = ta_lookup_chash_64;
	} else if ((cfg->mask6  % 8) == 0) {
		ti->data = (32 - cfg->mask4) << 24 |
		    cfg->mask6 << 13 | hsize;
		ti->lookup = ta_lookup_chash_aligned;
	} else {
		/* don't do that! */
		ti->data = (32 - cfg->mask4) << 24 |
		    cfg->mask6 << 16 | hsize;
		ti->lookup = ta_lookup_chash_slow;
	}

	return (0);
}