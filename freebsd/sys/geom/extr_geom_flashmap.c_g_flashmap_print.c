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
typedef  int uintmax_t ;
struct g_flashmap_slice {scalar_t__ sl_start; scalar_t__ sl_end; int /*<<< orphan*/  sl_name; } ;

/* Variables and functions */
 int /*<<< orphan*/  printf (char*,int,int,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static void
g_flashmap_print(struct g_flashmap_slice *slice)
{

	printf("%08jx-%08jx: %s (%juKB)\n", (uintmax_t)slice->sl_start,
	    (uintmax_t)slice->sl_end, slice->sl_name,
	    (uintmax_t)(slice->sl_end - slice->sl_start) / 1024);
}