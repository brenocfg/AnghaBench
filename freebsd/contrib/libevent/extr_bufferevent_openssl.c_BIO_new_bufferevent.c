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
struct bufferevent {int dummy; } ;
typedef  int /*<<< orphan*/  BIO ;

/* Variables and functions */
 int /*<<< orphan*/ * BIO_new (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_s_bufferevent () ; 
 int /*<<< orphan*/  BIO_set_data (int /*<<< orphan*/ *,struct bufferevent*) ; 
 int /*<<< orphan*/  BIO_set_init (int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  BIO_set_shutdown (int /*<<< orphan*/ *,int) ; 

__attribute__((used)) static BIO *
BIO_new_bufferevent(struct bufferevent *bufferevent, int close_flag)
{
	BIO *result;
	if (!bufferevent)
		return NULL;
	if (!(result = BIO_new(BIO_s_bufferevent())))
		return NULL;
	BIO_set_init(result, 1);
	BIO_set_data(result, bufferevent);
	BIO_set_shutdown(result, close_flag ? 1 : 0);
	return result;
}