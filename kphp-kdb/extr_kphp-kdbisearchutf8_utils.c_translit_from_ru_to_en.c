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
 int /*<<< orphan*/  _a_44_ ; 
 int /*<<< orphan*/  _a_45_ ; 
 int /*<<< orphan*/  _a_46_ ; 
 int /*<<< orphan*/  _a_47_ ; 
 int /*<<< orphan*/  _a_48_ ; 
 int /*<<< orphan*/  _a_49_ ; 
 int /*<<< orphan*/  _a_50_ ; 
 int /*<<< orphan*/  _a_51_ ; 
 int /*<<< orphan*/  _a_52_ ; 
 int /*<<< orphan*/  _a_53_ ; 
 int /*<<< orphan*/  _a_54_ ; 
 int /*<<< orphan*/  _a_55_ ; 
 int /*<<< orphan*/  _a_56_ ; 
 int /*<<< orphan*/  _a_57_ ; 
 int /*<<< orphan*/  _a_58_ ; 
 int /*<<< orphan*/  _a_59_ ; 
 int /*<<< orphan*/  _a_60_ ; 
 int /*<<< orphan*/  _a_61_ ; 
 int /*<<< orphan*/  _a_62_ ; 
 int /*<<< orphan*/  _a_63_ ; 
 int /*<<< orphan*/  _a_64_ ; 
 int /*<<< orphan*/  _a_65_ ; 
 int /*<<< orphan*/  _a_66_ ; 
 int /*<<< orphan*/  _a_67_ ; 
 int /*<<< orphan*/  _a_68_ ; 
 int /*<<< orphan*/  _a_69_ ; 
 int /*<<< orphan*/  _a_70_ ; 
 int /*<<< orphan*/  _a_71_ ; 
 int /*<<< orphan*/  _a_72_ ; 
 int /*<<< orphan*/  _a_73_ ; 
 int /*<<< orphan*/  _a_74_ ; 
 int /*<<< orphan*/  _a_75_ ; 
 int /*<<< orphan*/  _a_76_ ; 
 int /*<<< orphan*/  _a_77_ ; 
 int /*<<< orphan*/  _a_78_ ; 
 int /*<<< orphan*/  _a_79_ ; 
 int /*<<< orphan*/  _a_80_ ; 
 int /*<<< orphan*/  _a_81_ ; 
 int /*<<< orphan*/  _a_82_ ; 
 int /*<<< orphan*/  _a_83_ ; 
 long long _h_44_ ; 
 long long _h_45_ ; 
 long long _h_46_ ; 
 long long _h_47_ ; 
 long long _h_48_ ; 
 long long _h_49_ ; 
 long long _h_50_ ; 
 long long _h_51_ ; 
 long long _h_52_ ; 
 long long _h_53_ ; 
 long long _h_54_ ; 
 long long _h_55_ ; 
 long long _h_56_ ; 
 long long _h_57_ ; 
 long long _h_58_ ; 
 long long _h_59_ ; 
 long long _h_60_ ; 
 long long _h_61_ ; 
 long long _h_62_ ; 
 long long _h_63_ ; 
 long long _h_64_ ; 
 long long _h_65_ ; 
 long long _h_66_ ; 
 long long _h_67_ ; 
 long long _h_68_ ; 
 long long _h_69_ ; 
 long long _h_70_ ; 
 long long _h_71_ ; 
 long long _h_72_ ; 
 long long _h_73_ ; 
 long long _h_74_ ; 
 long long _h_75_ ; 
 long long _h_76_ ; 
 long long _h_77_ ; 
 long long _h_78_ ; 
 long long _h_79_ ; 
 long long _h_80_ ; 
 long long _h_81_ ; 
 long long _h_82_ ; 
 long long _h_83_ ; 
 int* _s_44_ ; 
 int* _s_45_ ; 
 int* _s_46_ ; 
 int* _s_47_ ; 
 int* _s_48_ ; 
 int* _s_49_ ; 
 int* _s_50_ ; 
 int* _s_51_ ; 
 int* _s_52_ ; 
 int* _s_53_ ; 
 int* _s_54_ ; 
 int* _s_55_ ; 
 int* _s_56_ ; 
 int* _s_57_ ; 
 int* _s_58_ ; 
 int* _s_59_ ; 
 int* _s_60_ ; 
 int* _s_61_ ; 
 int* _s_62_ ; 
 int* _s_63_ ; 
 int* _s_64_ ; 
 int* _s_65_ ; 
 int* _s_66_ ; 
 int* _s_67_ ; 
 int* _s_68_ ; 
 int* _s_69_ ; 
 int* _s_70_ ; 
 int* _s_71_ ; 
 int* _s_72_ ; 
 int* _s_73_ ; 
 int* _s_74_ ; 
 int* _s_75_ ; 
 int* _s_76_ ; 
 int* _s_77_ ; 
 int* _s_78_ ; 
 int* _s_79_ ; 
 int* _s_80_ ; 
 int* _s_81_ ; 
 int* _s_82_ ; 
 int* _s_83_ ; 

void translit_from_ru_to_en (int *s, long long *rh, int *hn) {

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
    case 1072://а
      //а --> a
      TEST(s, _s_44_, _h_44_, _a_44_);
      break;
    case 1073://б
      //б --> b
      TEST(s, _s_45_, _h_45_, _a_45_);
      break;
    case 1074://в
      //в --> v
      TEST(s, _s_46_, _h_46_, _a_46_);
      break;
    case 1075://г
      //г --> g
      TEST(s, _s_47_, _h_47_, _a_47_);
      break;
    case 1076://д
      //д --> d
      TEST(s, _s_48_, _h_48_, _a_48_);
      break;
    case 1077://е
      //е --> e
      TEST(s, _s_49_, _h_49_, _a_49_);
      break;
    case 1105://ё
      //ё --> e
      TEST(s, _s_50_, _h_50_, _a_50_);
      break;
    case 1078://ж
      //ж --> zh
      TEST(s, _s_51_, _h_51_, _a_51_);
      break;
    case 1079://з
      //з --> z
      TEST(s, _s_52_, _h_52_, _a_52_);
      break;
    case 1080://и
      //и --> i
      TEST(s, _s_53_, _h_53_, _a_53_);
      //ий --> y
      TEST(s, _s_54_, _h_54_, _a_54_);
      //ия --> ia
      TEST(s, _s_55_, _h_55_, _a_55_);
      break;
    case 1081://й
      //й --> y
      TEST(s, _s_56_, _h_56_, _a_56_);
      break;
    case 1082://к
      //к --> k
      TEST(s, _s_57_, _h_57_, _a_57_);
      //кс --> x
      TEST(s, _s_58_, _h_58_, _a_58_);
      break;
    case 1083://л
      //л --> l
      TEST(s, _s_59_, _h_59_, _a_59_);
      break;
    case 1084://м
      //м --> m
      TEST(s, _s_60_, _h_60_, _a_60_);
      break;
    case 1085://н
      //н --> n
      TEST(s, _s_61_, _h_61_, _a_61_);
      break;
    case 1086://о
      //о --> o
      TEST(s, _s_62_, _h_62_, _a_62_);
      break;
    case 1087://п
      //п --> p
      TEST(s, _s_63_, _h_63_, _a_63_);
      break;
    case 1088://р
      //р --> r
      TEST(s, _s_64_, _h_64_, _a_64_);
      break;
    case 1089://с
      //с --> s
      TEST(s, _s_65_, _h_65_, _a_65_);
      break;
    case 1090://т
      //т --> t
      TEST(s, _s_66_, _h_66_, _a_66_);
      break;
    case 1091://у
      //у --> u
      TEST(s, _s_67_, _h_67_, _a_67_);
      break;
    case 1092://ф
      //ф --> f
      TEST(s, _s_68_, _h_68_, _a_68_);
      break;
    case 1093://х
      //х --> kh
      TEST(s, _s_69_, _h_69_, _a_69_);
      break;
    case 1094://ц
      //ц --> ts
      TEST(s, _s_70_, _h_70_, _a_70_);
      break;
    case 1095://ч
      //ч --> ch
      TEST(s, _s_71_, _h_71_, _a_71_);
      break;
    case 1096://ш
      //ш --> sh
      TEST(s, _s_72_, _h_72_, _a_72_);
      break;
    case 1097://щ
      //щ --> shch
      TEST(s, _s_73_, _h_73_, _a_73_);
      break;
    case 1098://ъ
      //ъ -->
      TEST(s, _s_74_, _h_74_, _a_74_);
      break;
    case 1099://ы
      //ы --> y
      TEST(s, _s_75_, _h_75_, _a_75_);
      break;
    case 1100://ь
      //ь -->
      TEST(s, _s_76_, _h_76_, _a_76_);
      break;
    case 1101://э
      //э --> e
      TEST(s, _s_77_, _h_77_, _a_77_);
      break;
    case 1102://ю
      //ю --> yu
      TEST(s, _s_78_, _h_78_, _a_78_);
      break;
    case 1103://я
      //я --> ya
      TEST(s, _s_79_, _h_79_, _a_79_);
      break;
    case 121://y
      //y --> y
      TEST(s, _s_80_, _h_80_, _a_80_);
      //yo --> e
      TEST(s, _s_81_, _h_81_, _a_81_);
      break;
    case 106://j
      //j --> j
      TEST(s, _s_82_, _h_82_, _a_82_);
      //jo --> e
      TEST(s, _s_83_, _h_83_, _a_83_);
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