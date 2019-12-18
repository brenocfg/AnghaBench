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
 int /*<<< orphan*/  SWAP (char**,int,int) ; 
 int /*<<< orphan*/  add_list (char****,size_t*,char**,int const) ; 

__attribute__((used)) static void
permute(char ****list, size_t *listlen,
	char **str, const int start, const int len)
{
    int i, j;

#define SWAP(s,i,j) { char *t = str[i]; str[i] = str[j]; str[j] = t; }

    for (i = start; i < len - 1; i++) {
	for (j = i+1; j < len; j++) {
	    SWAP(str,i,j);
	    permute(list, listlen, str, i+1, len);
	    SWAP(str,i,j);
	}
    }
    add_list(list, listlen, str, len);
}