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
 int FSAFE ; 
 int dup (int) ; 
 int /*<<< orphan*/  xclose (int) ; 

__attribute__((used)) static int
renum(int i, int j)
{
    int k = dup(i);

    if (k < 0)
	return (-1);
    if (j == -1 && k > FSAFE)
	return (k);
    if (k != j) {
	j = renum(k, j);
	xclose(k);
	return (j);
    }
    return (k);
}