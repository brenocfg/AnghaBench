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
 int TLS_SCHEMA ; 
 int TLS_SCHEMA_V2 ; 

int get_schema_version (int a) {
  if (a == TLS_SCHEMA) {
    return 1;
  } if (a == TLS_SCHEMA_V2) {
    return 2;
  } else {
    return -1;
  }
}