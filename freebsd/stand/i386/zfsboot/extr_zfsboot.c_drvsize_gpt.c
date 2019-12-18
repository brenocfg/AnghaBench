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
typedef  scalar_t__ uint64_t ;
struct gpt_hdr {int hdr_lba_self; int hdr_revision; int hdr_entsz; scalar_t__ hdr_lba_alt; int /*<<< orphan*/  hdr_sig; } ;
struct gpt_ent {int dummy; } ;
struct dsk {int dummy; } ;
typedef  int /*<<< orphan*/  hdr ;
struct TYPE_2__ {char* secbuf; } ;

/* Variables and functions */
 int DEV_BSIZE ; 
 int /*<<< orphan*/  GPT_HDR_SIG ; 
 TYPE_1__* dmadat ; 
 scalar_t__ drvread (struct dsk*,char*,int,int) ; 
 scalar_t__ memcmp (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int) ; 
 int /*<<< orphan*/  memcpy (struct gpt_hdr*,char*,int) ; 

__attribute__((used)) static uint64_t
drvsize_gpt(struct dsk *dskp)
{
#ifdef GPT
	struct gpt_hdr hdr;
	char *sec;

	sec = dmadat->secbuf;
	if (drvread(dskp, sec, 1, 1))
		return (0);

	memcpy(&hdr, sec, sizeof(hdr));
	if (memcmp(hdr.hdr_sig, GPT_HDR_SIG, sizeof(hdr.hdr_sig)) != 0 ||
	    hdr.hdr_lba_self != 1 || hdr.hdr_revision < 0x00010000 ||
	    hdr.hdr_entsz < sizeof(struct gpt_ent) ||
	    DEV_BSIZE % hdr.hdr_entsz != 0) {
		return (0);
	}
	return (hdr.hdr_lba_alt + 1);
#else
	return (0);
#endif
}