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
typedef  int /*<<< orphan*/  u_long ;
typedef  void* u_int32_t ;

/* Variables and functions */
 int /*<<< orphan*/  des_init () ; 
 int /*<<< orphan*/  des_initialised ; 
 int do_des (void*,void*,void**,void**,int) ; 
 void* htonl (void*) ; 
 void* ntohl (void*) ; 
 int /*<<< orphan*/  setup_salt (int /*<<< orphan*/ ) ; 

__attribute__((used)) static int
des_cipher(const char *in, char *out, u_long salt, int count)
{
	u_int32_t	l_out, r_out, rawl, rawr;
	int		retval;
	union {
		u_int32_t	*ui32;
		const char	*c;
	} trans;

	if (!des_initialised)
		des_init();

	setup_salt(salt);

	trans.c = in;
	rawl = ntohl(*trans.ui32++);
	rawr = ntohl(*trans.ui32);

	retval = do_des(rawl, rawr, &l_out, &r_out, count);

	trans.c = out;
	*trans.ui32++ = htonl(l_out);
	*trans.ui32 = htonl(r_out);
	return(retval);
}