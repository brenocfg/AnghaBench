#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
typedef  int u_int32_t ;
typedef  scalar_t__ u_int16_t ;
struct csrreg {int val; int key; } ;
struct csrhdr {int info_len; int crc_len; int crc; } ;
struct csrdirectory {int crc_len; int crc; int /*<<< orphan*/ * entry; } ;
struct crom_context {int depth; TYPE_1__* stack; } ;
typedef  int /*<<< orphan*/  info ;
struct TYPE_2__ {struct csrdirectory* dir; } ;

/* Variables and functions */
 int CSRKEY_MASK ; 
 int CSRTYPE_MASK ; 
 scalar_t__ crom_crc (int*,int) ; 
 char* crom_desc (struct crom_context*,char*,int) ; 
 struct csrreg* crom_get (struct crom_context*) ; 
 int /*<<< orphan*/  crom_init_context (struct crom_context*,int*) ; 
 int /*<<< orphan*/  crom_next (struct crom_context*) ; 
 int /*<<< orphan*/  parse_bus_info_block (int*) ; 
 int /*<<< orphan*/  printf (char*,...) ; 

__attribute__((used)) static void
show_crom(u_int32_t *crom_buf)
{
	int i;
	struct crom_context cc;
	char *desc, info[256];
	static const char *key_types = "ICLD";
	struct csrreg *reg;
	struct csrdirectory *dir;
	struct csrhdr *hdr;
	u_int16_t crc;

	printf("first quad: 0x%08x ", *crom_buf);
	if (crom_buf[0] == 0) {
		printf("(Invalid Configuration ROM)\n");
		return;
	}
	hdr = (struct csrhdr *)crom_buf;
	if (hdr->info_len == 1) {
		/* minimum ROM */
		reg = (struct csrreg *)hdr;
		printf("verndor ID: 0x%06x\n",  reg->val);
		return;
	}
	printf("info_len=%d crc_len=%d crc=0x%04x",
		hdr->info_len, hdr->crc_len, hdr->crc);
	crc = crom_crc(crom_buf+1, hdr->crc_len);
	if (crc == hdr->crc)
		printf("(OK)\n");
	else
		printf("(NG)\n");
	parse_bus_info_block(crom_buf+1);

	crom_init_context(&cc, crom_buf);
	dir = cc.stack[0].dir;
	if (!dir) {
		printf("no root directory - giving up\n");
		return;
	}
	printf("root_directory: len=0x%04x(%d) crc=0x%04x",
			dir->crc_len, dir->crc_len, dir->crc);
	crc = crom_crc((u_int32_t *)&dir->entry[0], dir->crc_len);
	if (crc == dir->crc)
		printf("(OK)\n");
	else
		printf("(NG)\n");
	if (dir->crc_len < 1)
		return;
	while (cc.depth >= 0) {
		desc = crom_desc(&cc, info, sizeof(info));
		reg = crom_get(&cc);
		for (i = 0; i < cc.depth; i++)
			printf("\t");
		printf("%02x(%c:%02x) %06x %s: %s\n",
			reg->key,
			key_types[(reg->key & CSRTYPE_MASK)>>6],
			reg->key & CSRKEY_MASK, reg->val,
			desc, info);
		crom_next(&cc);
	}
}