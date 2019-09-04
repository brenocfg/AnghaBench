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
typedef  scalar_t__ DWORD ;

/* Variables and functions */
 scalar_t__ WSAEAFNOSUPPORT ; 
 scalar_t__ WSAEPFNOSUPPORT ; 
 scalar_t__ WSAEPROTONOSUPPORT ; 
 scalar_t__ WSAESOCKTNOSUPPORT ; 

__attribute__((used)) static int error_means_no_support(DWORD error) {
  return error == WSAEPROTONOSUPPORT || error == WSAESOCKTNOSUPPORT ||
         error == WSAEPFNOSUPPORT || error == WSAEAFNOSUPPORT;
}