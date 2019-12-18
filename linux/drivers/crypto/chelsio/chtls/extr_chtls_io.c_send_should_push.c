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
 int /*<<< orphan*/  corked (int /*<<< orphan*/ ,int) ; 
 scalar_t__ should_push (struct sock*) ; 
 int /*<<< orphan*/  tcp_sk (struct sock*) ; 

__attribute__((used)) static bool send_should_push(struct sock *sk, int flags)
{
	return should_push(sk) && !corked(tcp_sk(sk), flags);
}