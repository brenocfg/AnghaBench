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
 long long HASH_MUL ; 
 int /*<<< orphan*/  _a_10_ ; 
 int /*<<< orphan*/  _a_11_ ; 
 int /*<<< orphan*/  _a_12_ ; 
 int /*<<< orphan*/  _a_13_ ; 
 int /*<<< orphan*/  _a_14_ ; 
 int /*<<< orphan*/  _a_15_ ; 
 int /*<<< orphan*/  _a_16_ ; 
 int /*<<< orphan*/  _a_17_ ; 
 int /*<<< orphan*/  _a_18_ ; 
 int /*<<< orphan*/  _a_19_ ; 
 int /*<<< orphan*/  _a_1_ ; 
 int /*<<< orphan*/  _a_20_ ; 
 int /*<<< orphan*/  _a_21_ ; 
 int /*<<< orphan*/  _a_22_ ; 
 int /*<<< orphan*/  _a_23_ ; 
 int /*<<< orphan*/  _a_24_ ; 
 int /*<<< orphan*/  _a_25_ ; 
 int /*<<< orphan*/  _a_26_ ; 
 int /*<<< orphan*/  _a_27_ ; 
 int /*<<< orphan*/  _a_28_ ; 
 int /*<<< orphan*/  _a_29_ ; 
 int /*<<< orphan*/  _a_2_ ; 
 int /*<<< orphan*/  _a_30_ ; 
 int /*<<< orphan*/  _a_31_ ; 
 int /*<<< orphan*/  _a_32_ ; 
 int /*<<< orphan*/  _a_33_ ; 
 int /*<<< orphan*/  _a_34_ ; 
 int /*<<< orphan*/  _a_35_ ; 
 int /*<<< orphan*/  _a_36_ ; 
 int /*<<< orphan*/  _a_37_ ; 
 int /*<<< orphan*/  _a_38_ ; 
 int /*<<< orphan*/  _a_39_ ; 
 int /*<<< orphan*/  _a_3_ ; 
 int /*<<< orphan*/  _a_40_ ; 
 int /*<<< orphan*/  _a_41_ ; 
 int /*<<< orphan*/  _a_42_ ; 
 int /*<<< orphan*/  _a_43_ ; 
 int /*<<< orphan*/  _a_4_ ; 
 int /*<<< orphan*/  _a_5_ ; 
 int /*<<< orphan*/  _a_6_ ; 
 int /*<<< orphan*/  _a_7_ ; 
 int /*<<< orphan*/  _a_8_ ; 
 int /*<<< orphan*/  _a_9_ ; 
 long long _h_10_ ; 
 long long _h_11_ ; 
 long long _h_12_ ; 
 long long _h_13_ ; 
 long long _h_14_ ; 
 long long _h_15_ ; 
 long long _h_16_ ; 
 long long _h_17_ ; 
 long long _h_18_ ; 
 long long _h_19_ ; 
 long long _h_1_ ; 
 long long _h_20_ ; 
 long long _h_21_ ; 
 long long _h_22_ ; 
 long long _h_23_ ; 
 long long _h_24_ ; 
 long long _h_25_ ; 
 long long _h_26_ ; 
 long long _h_27_ ; 
 long long _h_28_ ; 
 long long _h_29_ ; 
 long long _h_2_ ; 
 long long _h_30_ ; 
 long long _h_31_ ; 
 long long _h_32_ ; 
 long long _h_33_ ; 
 long long _h_34_ ; 
 long long _h_35_ ; 
 long long _h_36_ ; 
 long long _h_37_ ; 
 long long _h_38_ ; 
 long long _h_39_ ; 
 long long _h_3_ ; 
 long long _h_40_ ; 
 long long _h_41_ ; 
 long long _h_42_ ; 
 long long _h_43_ ; 
 long long _h_4_ ; 
 long long _h_5_ ; 
 long long _h_6_ ; 
 long long _h_7_ ; 
 long long _h_8_ ; 
 long long _h_9_ ; 
 int* _s_10_ ; 
 int* _s_11_ ; 
 int* _s_12_ ; 
 int* _s_13_ ; 
 int* _s_14_ ; 
 int* _s_15_ ; 
 int* _s_16_ ; 
 int* _s_17_ ; 
 int* _s_18_ ; 
 int* _s_19_ ; 
 int* _s_1_ ; 
 int* _s_20_ ; 
 int* _s_21_ ; 
 int* _s_22_ ; 
 int* _s_23_ ; 
 int* _s_24_ ; 
 int* _s_25_ ; 
 int* _s_26_ ; 
 int* _s_27_ ; 
 int* _s_28_ ; 
 int* _s_29_ ; 
 int* _s_2_ ; 
 int* _s_30_ ; 
 int* _s_31_ ; 
 int* _s_32_ ; 
 int* _s_33_ ; 
 int* _s_34_ ; 
 int* _s_35_ ; 
 int* _s_36_ ; 
 int* _s_37_ ; 
 int* _s_38_ ; 
 int* _s_39_ ; 
 int* _s_3_ ; 
 int* _s_40_ ; 
 int* _s_41_ ; 
 int* _s_42_ ; 
 int* _s_43_ ; 
 int* _s_4_ ; 
 int* _s_5_ ; 
 int* _s_6_ ; 
 int* _s_7_ ; 
 int* _s_8_ ; 
 int* _s_9_ ; 

void translit_from_en_to_ru (int *s, long long *rh, int *hn) {

#define TEST(a, b, hm, ha) \
  i = 1;                         \
  while (a[i] && a[i] == b[i]) { \
    i++;                         \
  }                              \
  if (!a[i] || !b[i]) {          \
    nh = h * hm + ha;            \
    ns = a + i;                  \
  }                              \
  if (!*ns) {                    \
    rh[(*hn)++] = nh;            \
  }


#define PASS(a)                   \
  nh = h * HASH_MUL + a[0];       \
  ns = a + 1;                     \
  if (!*ns) {                     \
    rh[(*hn)++] = nh;             \
  }

  *hn = 0;
  int *ns = s, i;
  long long h = 0, nh = 0;

  while (*s) {
    switch (*s) {
    case 97://a
      //a --> а
      TEST(s, _s_1_, _h_1_, _a_1_);
      break;
    case 98://b
      //b --> б
      TEST(s, _s_2_, _h_2_, _a_2_);
      break;
    case 99://c
      //c --> к
      TEST(s, _s_3_, _h_3_, _a_3_);
      //ch --> ч
      TEST(s, _s_4_, _h_4_, _a_4_);
      break;
    case 100://d
      //d --> д
      TEST(s, _s_5_, _h_5_, _a_5_);
      break;
    case 101://e
      //e --> е
      TEST(s, _s_6_, _h_6_, _a_6_);
      //ei --> ей
      TEST(s, _s_7_, _h_7_, _a_7_);
      //ey --> ей
      TEST(s, _s_8_, _h_8_, _a_8_);
      break;
    case 102://f
      //f --> ф
      TEST(s, _s_9_, _h_9_, _a_9_);
      break;
    case 103://g
      //g --> г
      TEST(s, _s_10_, _h_10_, _a_10_);
      break;
    case 104://h
      //h --> х
      TEST(s, _s_11_, _h_11_, _a_11_);
      break;
    case 105://i
      //i --> и
      TEST(s, _s_12_, _h_12_, _a_12_);
      //ia --> ия
      TEST(s, _s_13_, _h_13_, _a_13_);
      //iy --> ий
      TEST(s, _s_14_, _h_14_, _a_14_);
      break;
    case 106://j
      //j --> й
      TEST(s, _s_15_, _h_15_, _a_15_);
      //jo --> ё
      TEST(s, _s_16_, _h_16_, _a_16_);
      //ju --> ю
      TEST(s, _s_17_, _h_17_, _a_17_);
      //ja --> я
      TEST(s, _s_18_, _h_18_, _a_18_);
      break;
    case 107://k
      //k --> к
      TEST(s, _s_19_, _h_19_, _a_19_);
      //kh --> х
      TEST(s, _s_20_, _h_20_, _a_20_);
      break;
    case 108://l
      //l --> л
      TEST(s, _s_21_, _h_21_, _a_21_);
      break;
    case 109://m
      //m --> м
      TEST(s, _s_22_, _h_22_, _a_22_);
      break;
    case 110://n
      //n --> н
      TEST(s, _s_23_, _h_23_, _a_23_);
      break;
    case 111://o
      //o --> о
      TEST(s, _s_24_, _h_24_, _a_24_);
      break;
    case 112://p
      //p --> п
      TEST(s, _s_25_, _h_25_, _a_25_);
      break;
    case 113://q
      //q --> к
      TEST(s, _s_26_, _h_26_, _a_26_);
      break;
    case 114://r
      //r --> р
      TEST(s, _s_27_, _h_27_, _a_27_);
      break;
    case 115://s
      //s --> с
      TEST(s, _s_28_, _h_28_, _a_28_);
      //sh --> ш
      TEST(s, _s_29_, _h_29_, _a_29_);
      //shch --> щ
      TEST(s, _s_30_, _h_30_, _a_30_);
      //sch --> щ
      TEST(s, _s_31_, _h_31_, _a_31_);
      break;
    case 116://t
      //t --> т
      TEST(s, _s_32_, _h_32_, _a_32_);
      //ts --> ц
      TEST(s, _s_33_, _h_33_, _a_33_);
      break;
    case 117://u
      //u --> у
      TEST(s, _s_34_, _h_34_, _a_34_);
      break;
    case 118://v
      //v --> в
      TEST(s, _s_35_, _h_35_, _a_35_);
      break;
    case 119://w
      //w --> в
      TEST(s, _s_36_, _h_36_, _a_36_);
      break;
    case 120://x
      //x --> кс
      TEST(s, _s_37_, _h_37_, _a_37_);
      break;
    case 121://y
      //y --> и
      TEST(s, _s_38_, _h_38_, _a_38_);
      //yo --> ё
      TEST(s, _s_39_, _h_39_, _a_39_);
      //yu --> ю
      TEST(s, _s_40_, _h_40_, _a_40_);
      //ya --> я
      TEST(s, _s_41_, _h_41_, _a_41_);
      break;
    case 122://z
      //z --> з
      TEST(s, _s_42_, _h_42_, _a_42_);
      //zh --> ж
      TEST(s, _s_43_, _h_43_, _a_43_);
      break;
    default:
      PASS(s);
    }
    s = ns++;
    h = nh;
  }
#undef TEST
#undef PASS
}