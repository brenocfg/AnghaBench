#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct TYPE_2__ {unsigned long n_written; unsigned long n_read; } ;
struct bufferevent_openssl {TYPE_1__ counts; int /*<<< orphan*/  bev; int /*<<< orphan*/  ssl; } ;

/* Variables and functions */
 unsigned long BIO_number_read (int /*<<< orphan*/ ) ; 
 unsigned long BIO_number_written (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_get_rbio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_get_wbio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  bufferevent_decrement_read_buckets_ (int /*<<< orphan*/ *,unsigned long) ; 
 int /*<<< orphan*/  bufferevent_decrement_write_buckets_ (int /*<<< orphan*/ *,unsigned long) ; 

__attribute__((used)) static inline void
decrement_buckets(struct bufferevent_openssl *bev_ssl)
{
	unsigned long num_w = BIO_number_written(SSL_get_wbio(bev_ssl->ssl));
	unsigned long num_r = BIO_number_read(SSL_get_rbio(bev_ssl->ssl));
	/* These next two subtractions can wrap around. That's okay. */
	unsigned long w = num_w - bev_ssl->counts.n_written;
	unsigned long r = num_r - bev_ssl->counts.n_read;
	if (w)
		bufferevent_decrement_write_buckets_(&bev_ssl->bev, w);
	if (r)
		bufferevent_decrement_read_buckets_(&bev_ssl->bev, r);
	bev_ssl->counts.n_written = num_w;
	bev_ssl->counts.n_read = num_r;
}