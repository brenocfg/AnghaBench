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
typedef  int u_short ;
typedef  int u_char ;

/* Variables and functions */
#define  PROTO_CHAP 129 
#define  PROTO_PAP 128 
 int /*<<< orphan*/  snprintf (char*,int,char*,int) ; 

const char *
Auth2Nam(u_short auth, u_char type)
{
  static char chap[10];

  switch (auth) {
  case PROTO_PAP:
    return "PAP";
  case PROTO_CHAP:
    snprintf(chap, sizeof chap, "CHAP 0x%02x", type);
    return chap;
  case 0:
    return "none";
  }
  return "unknown";
}