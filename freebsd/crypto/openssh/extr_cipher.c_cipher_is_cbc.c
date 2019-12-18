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
typedef  int u_int ;
struct sshcipher {int flags; } ;

/* Variables and functions */
 int CFLAG_CBC ; 

u_int
cipher_is_cbc(const struct sshcipher *c)
{
	return (c->flags & CFLAG_CBC) != 0;
}