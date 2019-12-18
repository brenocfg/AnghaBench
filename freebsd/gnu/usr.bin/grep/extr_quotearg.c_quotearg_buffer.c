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
struct quoting_options {int /*<<< orphan*/  style; } ;

/* Variables and functions */
 struct quoting_options const default_quoting_options ; 
 size_t quotearg_buffer_restyled (char*,size_t,char const*,size_t,int /*<<< orphan*/ ,struct quoting_options const*) ; 

size_t
quotearg_buffer (char *buffer, size_t buffersize,
		 char const *arg, size_t argsize,
		 struct quoting_options const *o)
{
  struct quoting_options const *p = o ? o : &default_quoting_options;
  return quotearg_buffer_restyled (buffer, buffersize, arg, argsize,
				   p->style, p);
}