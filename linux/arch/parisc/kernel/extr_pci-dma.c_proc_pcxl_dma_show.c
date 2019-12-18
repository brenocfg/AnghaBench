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
typedef  int u_long ;
struct seq_file {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  PCXL_DMA_MAP_SIZE ; 
 int /*<<< orphan*/  buf ; 
 scalar_t__ pcxl_res_map ; 
 int pcxl_res_size ; 
 int pcxl_used_bytes ; 
 unsigned long pcxl_used_pages ; 
 int /*<<< orphan*/  seq_printf (struct seq_file*,char*,int,...) ; 
 int /*<<< orphan*/  seq_putc (struct seq_file*,char) ; 
 int /*<<< orphan*/  seq_puts (struct seq_file*,char*) ; 

__attribute__((used)) static int proc_pcxl_dma_show(struct seq_file *m, void *v)
{
#if 0
	u_long i = 0;
	unsigned long *res_ptr = (u_long *)pcxl_res_map;
#endif
	unsigned long total_pages = pcxl_res_size << 3;   /* 8 bits per byte */

	seq_printf(m, "\nDMA Mapping Area size    : %d bytes (%ld pages)\n",
		PCXL_DMA_MAP_SIZE, total_pages);

	seq_printf(m, "Resource bitmap : %d bytes\n", pcxl_res_size);

	seq_puts(m,  "     	  total:    free:    used:   % used:\n");
	seq_printf(m, "blocks  %8d %8ld %8ld %8ld%%\n", pcxl_res_size,
		pcxl_res_size - pcxl_used_bytes, pcxl_used_bytes,
		(pcxl_used_bytes * 100) / pcxl_res_size);

	seq_printf(m, "pages   %8ld %8ld %8ld %8ld%%\n", total_pages,
		total_pages - pcxl_used_pages, pcxl_used_pages,
		(pcxl_used_pages * 100 / total_pages));

#if 0
	seq_puts(m, "\nResource bitmap:");

	for(; i < (pcxl_res_size / sizeof(u_long)); ++i, ++res_ptr) {
		if ((i & 7) == 0)
		    seq_puts(m,"\n   ");
		seq_printf(m, "%s %08lx", buf, *res_ptr);
	}
#endif
	seq_putc(m, '\n');
	return 0;
}