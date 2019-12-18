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
struct ldat {struct ldat* text; } ;

/* Variables and functions */
 int ERR ; 
 int /*<<< orphan*/  free (struct ldat*) ; 

__attribute__((used)) static int
cleanup_lines(struct ldat *data, int length)
{
    while (--length >= 0)
	free(data[length].text);
    free(data);
    return ERR;
}