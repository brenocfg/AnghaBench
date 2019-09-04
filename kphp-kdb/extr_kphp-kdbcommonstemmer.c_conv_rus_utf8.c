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

inline int conv_rus_utf8 (const int c) {
  switch (c) {
    case 1081://é
      return 9;
    case 1094://ö
      return 22;
    case 1091://ó
      return 19;
    case 1082://ê
      return 10;
    case 1077://å
      return 5;
    case 1085://í
      return 13;
    case 1075://ã
      return 3;
    case 1096://ø
      return 24;
    case 1097://ù
      return 25;
    case 1079://ç
      return 7;
    case 1093://õ
      return 21;
    case 1098://ú
      return 26;
    case 1092://ô
      return 20;
    case 1099://û
      return 27;
    case 1074://â
      return 2;
    case 1072://à
      return 0;
    case 1087://ï
      return 15;
    case 1088://ğ
      return 16;
    case 1086://î
      return 14;
    case 1083://ë
      return 11;
    case 1076://ä
      return 4;
    case 1078://æ
      return 6;
    case 1101://ı
      return 29;
    case 1103://ÿ
      return 31;
    case 1095://÷
      return 23;
    case 1089://ñ
      return 17;
    case 1084://ì
      return 12;
    case 1080://è
      return 8;
    case 1090://ò
      return 18;
    case 1100://ü
      return 28;
    case 1073://á
      return 1;
    case 1102://ş
      return 30;
    case 1105://¸
      return 5;
    case 1049://É
      return 9;
    case 1062://Ö
      return 22;
    case 1059://Ó
      return 19;
    case 1050://Ê
      return 10;
    case 1045://Å
      return 5;
    case 1053://Í
      return 13;
    case 1043://Ã
      return 3;
    case 1064://Ø
      return 24;
    case 1065://Ù
      return 25;
    case 1047://Ç
      return 7;
    case 1061://Õ
      return 21;
    case 1066://Ú
      return 26;
    case 1060://Ô
      return 20;
    case 1067://Û
      return 27;
    case 1042://Â
      return 2;
    case 1040://À
      return 0;
    case 1055://Ï
      return 15;
    case 1056://Ğ
      return 16;
    case 1054://Î
      return 14;
    case 1051://Ë
      return 11;
    case 1044://Ä
      return 4;
    case 1046://Æ
      return 6;
    case 1069://İ
      return 29;
    case 1071://ß
      return 31;
    case 1063://×
      return 23;
    case 1057://Ñ
      return 17;
    case 1052://Ì
      return 12;
    case 1048://È
      return 8;
    case 1058://Ò
      return 18;
    case 1068://Ü
      return 28;
    case 1041://Á
      return 1;
    case 1070://Ş
      return 30;
    case 1025://¨
      return 5;
    default:
      return 33;
  }
}