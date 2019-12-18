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
struct quoting_options {int dummy; } ;

/* Variables and functions */
 struct quoting_options default_quoting_options ; 
 scalar_t__ xmalloc (int) ; 

struct quoting_options *
clone_quoting_options (struct quoting_options *o)
{
  struct quoting_options *p
    = (struct quoting_options *) xmalloc (sizeof (struct quoting_options));
  *p = *(o ? o : &default_quoting_options);
  return p;
}