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
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  build_segment_config (char*,unsigned int) ; 
 unsigned int read_c0_segctl0 () ; 
 unsigned int read_c0_segctl1 () ; 
 unsigned int read_c0_segctl2 () ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,char*) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int show_segments(struct seq_file *m, void *v)
{
	unsigned int segcfg;
	char str[42];

	seq_puts(m, "Segment   Virtual    Size   Access Mode   Physical   Caching   EU\n");
	seq_puts(m, "-------   -------    ----   -----------   --------   -------   --\n");

	segcfg = read_c0_segctl0();
	build_segment_config(str, segcfg);
	seq_printf(m, "   0      e0000000   512M      %s", str);

	segcfg >>= 16;
	build_segment_config(str, segcfg);
	seq_printf(m, "   1      c0000000   512M      %s", str);

	segcfg = read_c0_segctl1();
	build_segment_config(str, segcfg);
	seq_printf(m, "   2      a0000000   512M      %s", str);

	segcfg >>= 16;
	build_segment_config(str, segcfg);
	seq_printf(m, "   3      80000000   512M      %s", str);

	segcfg = read_c0_segctl2();
	build_segment_config(str, segcfg);
	seq_printf(m, "   4      40000000    1G       %s", str);

	segcfg >>= 16;
	build_segment_config(str, segcfg);
	seq_printf(m, "   5      00000000    1G       %s\n", str);

	return 0;
}