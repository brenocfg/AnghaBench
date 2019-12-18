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
struct TYPE_2__ {int /*<<< orphan*/  n_read; int /*<<< orphan*/  n_written; } ;
struct bufferevent_openssl {int /*<<< orphan*/  ssl; TYPE_1__ counts; } ;

/* Variables and functions */
 int /*<<< orphan*/  BIO_number_read (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  BIO_number_written (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_get_rbio (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  SSL_get_wbio (int /*<<< orphan*/ ) ; 

__attribute__((used)) static void
init_bio_counts(struct bufferevent_openssl *bev_ssl)
{
	bev_ssl->counts.n_written =
	    BIO_number_written(SSL_get_wbio(bev_ssl->ssl));
	bev_ssl->counts.n_read =
	    BIO_number_read(SSL_get_rbio(bev_ssl->ssl));
}