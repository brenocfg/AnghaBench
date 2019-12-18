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
struct type {int dummy; } ;

/* Variables and functions */
 scalar_t__ DEPRECATED_REGISTER_RAW_SIZE (int) ; 
 scalar_t__ TYPE_LENGTH (struct type*) ; 
 double deprecated_extract_floating (char const*,scalar_t__) ; 
 int /*<<< orphan*/  deprecated_store_floating (char*,scalar_t__,double) ; 
 int /*<<< orphan*/  memcpy (char*,char const*,scalar_t__) ; 

__attribute__((used)) static void
rs6000_register_convert_to_raw (struct type *type, int n,
				const char *from, char *to)
{
  if (TYPE_LENGTH (type) != DEPRECATED_REGISTER_RAW_SIZE (n))
    {
      double val = deprecated_extract_floating (from, TYPE_LENGTH (type));
      deprecated_store_floating (to, DEPRECATED_REGISTER_RAW_SIZE (n), val);
    }
  else
    memcpy (to, from, DEPRECATED_REGISTER_RAW_SIZE (n));
}