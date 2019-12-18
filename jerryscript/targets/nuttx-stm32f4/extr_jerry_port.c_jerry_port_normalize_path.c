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

/* Variables and functions */
 int /*<<< orphan*/  strcpy (char*,char const*) ; 
 size_t strlen (char const*) ; 

size_t
jerry_port_normalize_path (const char *in_path_p,   /**< input file path */
                           char *out_buf_p,         /**< output buffer */
                           size_t out_buf_size,     /**< size of output buffer */
                           char *base_file_p) /**< base file path */
{
  (void) base_file_p;

  size_t len = strlen (in_path_p);
  if (len + 1 > out_buf_size)
  {
    return 0;
  }

  /* Return the original string. */
  strcpy (out_buf_p, in_path_p);
  return len;
}