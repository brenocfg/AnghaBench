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
struct ata_params {int /*<<< orphan*/  serial; int /*<<< orphan*/  revision; int /*<<< orphan*/  model; } ;
typedef  int /*<<< orphan*/  int16_t ;

/* Variables and functions */
 int /*<<< orphan*/  ata_bpack (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ata_bswap (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  ata_btrim (int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  le16toh (int /*<<< orphan*/ ) ; 
 scalar_t__ strncmp (int /*<<< orphan*/ ,char*,int) ; 

void
ata_param_fixup(struct ata_params *ident_buf)
{
	int16_t *ptr;

	for (ptr = (int16_t *)ident_buf;
	     ptr < (int16_t *)ident_buf + sizeof(struct ata_params)/2; ptr++) {
		*ptr = le16toh(*ptr);
	}
	if (strncmp(ident_buf->model, "FX", 2) &&
	    strncmp(ident_buf->model, "NEC", 3) &&
	    strncmp(ident_buf->model, "Pioneer", 7) &&
	    strncmp(ident_buf->model, "SHARP", 5)) {
		ata_bswap(ident_buf->model, sizeof(ident_buf->model));
		ata_bswap(ident_buf->revision, sizeof(ident_buf->revision));
		ata_bswap(ident_buf->serial, sizeof(ident_buf->serial));
	}
	ata_btrim(ident_buf->model, sizeof(ident_buf->model));
	ata_bpack(ident_buf->model, ident_buf->model, sizeof(ident_buf->model));
	ata_btrim(ident_buf->revision, sizeof(ident_buf->revision));
	ata_bpack(ident_buf->revision, ident_buf->revision, sizeof(ident_buf->revision));
	ata_btrim(ident_buf->serial, sizeof(ident_buf->serial));
	ata_bpack(ident_buf->serial, ident_buf->serial, sizeof(ident_buf->serial));
}