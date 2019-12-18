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
typedef  int uint64_t ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 int EOF ; 
 int UINT64_MAX ; 
 int fgetc (int /*<<< orphan*/ *) ; 

__attribute__((used)) static uint64_t read_int(FILE *fp, size_t nbytes)
{
    uint64_t v = 0;
    size_t i;
    int ch;
    for (i = 0; i != nbytes; ++i) {
        if ((ch = fgetc(fp)) == EOF)
            return UINT64_MAX;
        v = (v << 8) | ch;
    }
    return v;
}