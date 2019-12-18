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
 int A ; 
 int B ; 
 int diff ; 
 scalar_t__ is_letter (int) ; 
 int len ; 
 float logf (float) ; 
 float** prob ; 
 float* ratings ; 
 scalar_t__ translit ; 
 scalar_t__ try ; 

float get_rating (const int a) {
  float res = logf (ratings[a] + 1.0f) / logf (2.0f);

  if (translit) {
    res /= 1.3;
  }

  if (diff != -1) {
    res *= (diff + 2 * len + 1);
    res /= (6 * len + 3);

    if (len <= 6) {
      res /= (7 - len);
    }

#ifdef SLOW
    if (A != B) {
      if (is_letter (A) && is_letter (B)) {
        res *= prob[A % 1072 % 128][B % 1072 % 128];
      } else {
        res *= 0.5f;
      }
    }
#endif
  }

  if (try) {
    res /= 10;

    if (translit) {
      res /= 2;
    }
  }

  return res;
}