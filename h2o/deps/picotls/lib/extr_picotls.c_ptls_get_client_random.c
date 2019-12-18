#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int /*<<< orphan*/  client_random; } ;
typedef  TYPE_1__ ptls_t ;
typedef  int /*<<< orphan*/  ptls_iovec_t ;

/* Variables and functions */
 int /*<<< orphan*/  PTLS_HELLO_RANDOM_SIZE ; 
 int /*<<< orphan*/  ptls_iovec_init (int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 

ptls_iovec_t ptls_get_client_random(ptls_t *tls)
{
    return ptls_iovec_init(tls->client_random, PTLS_HELLO_RANDOM_SIZE);
}