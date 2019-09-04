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
typedef  size_t GSortField ;

/* Variables and functions */

const char *
get_sort_field_key (GSortField field)
{
  static const char *field2key[][2] = {
    {"BY_HITS", "hits"},
    {"BY_VISITORS", "visitors"},
    {"BY_DATA", "data"},
    {"BY_BW", "bytes"},
    {"BY_AVGTS", "avgts"},
    {"BY_CUMTS", "cumts"},
    {"BY_MAXTS", "maxts"},
    {"BY_PROT", "protocol"},
    {"BY_MTHD", "method"},
  };

  return field2key[field][1];
}