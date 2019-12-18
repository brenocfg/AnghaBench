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
struct sock {int dummy; } ;

/* Variables and functions */
 int SKB_MAX_HEAD (int) ; 
 int /*<<< orphan*/  send_should_push (struct sock*,int) ; 

__attribute__((used)) static int select_size(struct sock *sk, int io_len, int flags, int len)
{
	const int pgbreak = SKB_MAX_HEAD(len);

	/*
	 * If the data wouldn't fit in the main body anyway, put only the
	 * header in the main body so it can use immediate data and place all
	 * the payload in page fragments.
	 */
	if (io_len > pgbreak)
		return 0;

	/*
	 * If we will be accumulating payload get a large main body.
	 */
	if (!send_should_push(sk, flags))
		return pgbreak;

	return io_len;
}