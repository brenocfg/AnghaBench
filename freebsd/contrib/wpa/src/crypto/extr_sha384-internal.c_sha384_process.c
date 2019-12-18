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
struct sha384_state {int dummy; } ;

/* Variables and functions */
 int sha512_process (struct sha384_state*,unsigned char const*,unsigned long) ; 

int sha384_process(struct sha384_state *md, const unsigned char *in,
		   unsigned long inlen)
{
	return sha512_process(md, in, inlen);
}