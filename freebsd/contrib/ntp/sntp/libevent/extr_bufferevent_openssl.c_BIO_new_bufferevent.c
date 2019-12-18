#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct bufferevent {int dummy; } ;
struct TYPE_4__ {int init; int shutdown; struct bufferevent* ptr; } ;
typedef  TYPE_1__ BIO ;

/* Variables and functions */
 TYPE_1__* BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_bufferevent () ; 

__attribute__((used)) static BIO *
BIO_new_bufferevent(struct bufferevent *bufferevent, int close_flag)
{
	BIO *result;
	if (!bufferevent)
		return NULL;
	if (!(result = BIO_new(BIO_s_bufferevent())))
		return NULL;
	result->init = 1;
	result->ptr = bufferevent;
	result->shutdown = close_flag ? 1 : 0;
	return result;
}