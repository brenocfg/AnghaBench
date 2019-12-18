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
struct seqbuf {scalar_t__ pos; scalar_t__ size; } ;

/* Variables and functions */
 size_t EOVERFLOW ; 

__attribute__((used)) static size_t seqbuf_status(struct seqbuf *seqbuf)
{
	return seqbuf->pos <= seqbuf->size ? 0 : -EOVERFLOW;
}