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
struct trace_key {int /*<<< orphan*/  key; } ;

/* Variables and functions */
 int /*<<< orphan*/  errno ; 
 int /*<<< orphan*/  get_trace_fd (struct trace_key*) ; 
 int /*<<< orphan*/  strerror (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  trace_disable (struct trace_key*) ; 
 int /*<<< orphan*/  warning (char*,int /*<<< orphan*/ ,int /*<<< orphan*/ ) ; 
 scalar_t__ write_in_full (int /*<<< orphan*/ ,void const*,unsigned int) ; 

__attribute__((used)) static void trace_write(struct trace_key *key, const void *buf, unsigned len)
{
	if (write_in_full(get_trace_fd(key), buf, len) < 0) {
		warning("unable to write trace for %s: %s",
			key->key, strerror(errno));
		trace_disable(key);
	}
}