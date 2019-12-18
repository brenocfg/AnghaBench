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
 char* XML_ExpatVersion () ; 
 int /*<<< orphan*/  strncmp (char const*,char*,int) ; 

const char *
svn_xml__runtime_version(void)
{
  const char *expat_version = XML_ExpatVersion();

  if (!strncmp(expat_version, "expat_", 6))
    expat_version += 6;

  return expat_version;
}