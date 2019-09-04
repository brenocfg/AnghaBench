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
typedef  int /*<<< orphan*/  GRawData ;
typedef  int GModule ;

/* Variables and functions */
#define  VISITORS 128 
 int /*<<< orphan*/ * parse_raw_num_data (int) ; 
 int /*<<< orphan*/ * parse_raw_str_data (int) ; 

GRawData *
parse_raw_data (GModule module)
{
  GRawData *raw_data;

  switch (module) {
  case VISITORS:
    raw_data = parse_raw_str_data (module);
    break;
  default:
    raw_data = parse_raw_num_data (module);
  }
  return raw_data;
}