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
typedef  int /*<<< orphan*/  SSL_CTX ;

/* Variables and functions */
 int /*<<< orphan*/  setup_cache_enable (int /*<<< orphan*/ **,size_t,int /*<<< orphan*/ ) ; 

__attribute__((used)) static void setup_cache_internal(SSL_CTX **contexts, size_t num_contexts)
{
    setup_cache_enable(contexts, num_contexts, 0);
}