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

/* Variables and functions */
 int /*<<< orphan*/  printf (char*) ; 

__attribute__((used)) static int
print_padding(int fromcol, int tocol) {
    int col = fromcol, nextcol = fromcol + 8 - fromcol%8;

    if (fromcol + 1 > tocol) tocol = fromcol + 1;
    for (; nextcol <= tocol; col = nextcol, nextcol += 8)
        printf("\t");
    for (; col < tocol; col++)
        printf(" ");
    return col - fromcol;
}