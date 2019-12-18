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
 int /*<<< orphan*/  krb5_generate_random_block (unsigned char*,int) ; 

__attribute__((used)) static int
RND(unsigned char *key, int keylen, int *left)
{
    if(*left == 0){
	krb5_generate_random_block(key, keylen);
	*left = keylen;
    }
    (*left)--;
    return ((unsigned char*)key)[*left];
}