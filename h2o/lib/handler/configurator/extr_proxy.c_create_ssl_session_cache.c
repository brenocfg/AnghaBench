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
typedef  int /*<<< orphan*/  uint64_t ;
typedef  int /*<<< orphan*/  h2o_cache_t ;

/* Variables and functions */
 int /*<<< orphan*/  H2O_CACHE_FLAG_MULTITHREADED ; 
 int /*<<< orphan*/ * h2o_cache_create (int /*<<< orphan*/ ,size_t,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  h2o_socket_ssl_destroy_session_cache_entry ; 

__attribute__((used)) static h2o_cache_t *create_ssl_session_cache(size_t capacity, uint64_t duration)
{
    return h2o_cache_create(H2O_CACHE_FLAG_MULTITHREADED, capacity, duration, h2o_socket_ssl_destroy_session_cache_entry);
}