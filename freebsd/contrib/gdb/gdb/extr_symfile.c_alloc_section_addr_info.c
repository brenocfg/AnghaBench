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
struct section_addr_info {size_t num_sections; } ;
struct other_sections {int dummy; } ;

/* Variables and functions */
 int /*<<< orphan*/  memset (struct section_addr_info*,int /*<<< orphan*/ ,size_t) ; 
 scalar_t__ xmalloc (size_t) ; 

struct section_addr_info *
alloc_section_addr_info (size_t num_sections)
{
  struct section_addr_info *sap;
  size_t size;

  size = (sizeof (struct section_addr_info)
	  +  sizeof (struct other_sections) * (num_sections - 1));
  sap = (struct section_addr_info *) xmalloc (size);
  memset (sap, 0, size);
  sap->num_sections = num_sections;

  return sap;
}