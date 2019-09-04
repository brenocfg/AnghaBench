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

inline int bad_letters (int x) {
  switch (x) {
  case 1093://õ
  case 1098://ú
  case 1078://æ
  case 1101://ý
  case 1073://á
  case 1102://þ
  case 1105://¸
  case 1061://Õ
  case 1066://Ú
  case 1046://Æ
  case 1069://Ý
  case 1041://Á
  case 1070://Þ
  case 1025://¨
    return 1;
  }
  return 0;
}