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
typedef  int u32 ;
struct device {int dummy; } ;
typedef  int /*<<< orphan*/  __be32 ;

/* Variables and functions */
 int FFDC_LSIZE ; 
 int be32_to_cpu (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  dev_err (struct device*,char*,int,...) ; 
 int /*<<< orphan*/  dev_warn (struct device*,char*,...) ; 
 int /*<<< orphan*/  sprintf (char*,char*,...) ; 

__attribute__((used)) static void __sbefifo_dump_ffdc(struct device *dev, const __be32 *ffdc,
				size_t ffdc_sz, bool internal)
{
	int pack = 0;
#define FFDC_LSIZE	60
	static char ffdc_line[FFDC_LSIZE];
	char *p = ffdc_line;

	while (ffdc_sz) {
		u32 w0, w1, w2, i;
		if (ffdc_sz < 3) {
			dev_err(dev, "SBE invalid FFDC package size %zd\n", ffdc_sz);
			return;
		}
		w0 = be32_to_cpu(*(ffdc++));
		w1 = be32_to_cpu(*(ffdc++));
		w2 = be32_to_cpu(*(ffdc++));
		ffdc_sz -= 3;
		if ((w0 >> 16) != 0xFFDC) {
			dev_err(dev, "SBE invalid FFDC package signature %08x %08x %08x\n",
				w0, w1, w2);
			break;
		}
		w0 &= 0xffff;
		if (w0 > ffdc_sz) {
			dev_err(dev, "SBE FFDC package len %d words but only %zd remaining\n",
				w0, ffdc_sz);
			w0 = ffdc_sz;
			break;
		}
		if (internal) {
			dev_warn(dev, "+---- SBE FFDC package %d for async err -----+\n",
				 pack++);
		} else {
			dev_warn(dev, "+---- SBE FFDC package %d for cmd %02x:%02x -----+\n",
				 pack++, (w1 >> 8) & 0xff, w1 & 0xff);
		}
		dev_warn(dev, "| Response code: %08x                   |\n", w2);
		dev_warn(dev, "|-------------------------------------------|\n");
		for (i = 0; i < w0; i++) {
			if ((i & 3) == 0) {
				p = ffdc_line;
				p += sprintf(p, "| %04x:", i << 4);
			}
			p += sprintf(p, " %08x", be32_to_cpu(*(ffdc++)));
			ffdc_sz--;
			if ((i & 3) == 3 || i == (w0 - 1)) {
				while ((i & 3) < 3) {
					p += sprintf(p, "         ");
					i++;
				}
				dev_warn(dev, "%s |\n", ffdc_line);
			}
		}
		dev_warn(dev, "+-------------------------------------------+\n");
	}
}