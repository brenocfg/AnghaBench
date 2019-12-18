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
typedef  int /*<<< orphan*/  quicly_stream_t ;
typedef  int /*<<< orphan*/  quicly_context_t ;

/* Variables and functions */
 int /*<<< orphan*/ * malloc (int) ; 

quicly_stream_t *quicly_default_alloc_stream(quicly_context_t *ctx)
{
    return malloc(sizeof(quicly_stream_t));
}