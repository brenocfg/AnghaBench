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
 char* alloc_string (char const*) ; 
 scalar_t__ strstr (char const*,char*) ; 

__attribute__((used)) static char *
get_real_mac_osx (const char *osx)
{
  if (strstr (osx, "10.14"))
    return alloc_string ("macOS 10.14 Mojave");
  else if (strstr (osx, "10.13"))
    return alloc_string ("macOS 10.13 High Sierra");
  else if (strstr (osx, "10.12"))
    return alloc_string ("macOS 10.12 Sierra");
  else if (strstr (osx, "10.11"))
    return alloc_string ("OS X 10.11 El Capitan");
  else if (strstr (osx, "10.10"))
    return alloc_string ("OS X 10.10 Yosemite");
  else if (strstr (osx, "10.9"))
    return alloc_string ("OS X 10.9 Mavericks");
  else if (strstr (osx, "10.8"))
    return alloc_string ("OS X 10.8 Mountain Lion");
  else if (strstr (osx, "10.7"))
    return alloc_string ("OS X 10.7 Lion");
  else if (strstr (osx, "10.6"))
    return alloc_string ("OS X 10.6 Snow Leopard");
  else if (strstr (osx, "10.5"))
    return alloc_string ("OS X 10.5 Leopard");
  else if (strstr (osx, "10.4"))
    return alloc_string ("OS X 10.4 Tiger");
  else if (strstr (osx, "10.3"))
    return alloc_string ("OS X 10.3 Panther");
  else if (strstr (osx, "10.2"))
    return alloc_string ("OS X 10.2 Jaguar");
  else if (strstr (osx, "10.1"))
    return alloc_string ("OS X 10.1 Puma");
  else if (strstr (osx, "10.0"))
    return alloc_string ("OS X 10.0 Cheetah");
  return alloc_string (osx);
}