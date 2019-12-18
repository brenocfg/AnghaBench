#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
struct scfg {scalar_t__ flag2; scalar_t__ flag1; } ;
struct TYPE_5__ {struct scfg* enc_private; } ;
typedef  TYPE_1__ enc_softc_t ;

/* Variables and functions */
 int /*<<< orphan*/  DELAY (int) ; 
 int ENXIO ; 
#define  SEND_DIAGNOSTIC 128 
 int enc_runcmd (TYPE_1__*,char*,int,int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int safte_set_enc_status (TYPE_1__*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static int
safte_init_enc(enc_softc_t *enc)
{
	struct scfg *cfg;
	int err;
	static char cdb0[6] = { SEND_DIAGNOSTIC };

	cfg = enc->enc_private;
	if (cfg == NULL)
		return (ENXIO);

	err = enc_runcmd(enc, cdb0, 6, NULL, 0);
	if (err) {
		return (err);
	}
	DELAY(5000);
	cfg->flag1 = 0;
	cfg->flag2 = 0;
	err = safte_set_enc_status(enc, 0, 1);
	return (err);
}