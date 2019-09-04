#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct query_keyword_descr {int flags; int minv; int maxv; scalar_t__ q_type; int /*<<< orphan*/ * str; } ;
struct TYPE_6__ {int flags; int complexity; scalar_t__ type; int value2; int value; struct TYPE_6__* left; } ;
typedef  TYPE_1__ query_t ;

/* Variables and functions */
 int MAXINT ; 
 int MININT ; 
 char* Qs ; 
 struct query_keyword_descr* QueryKW ; 
 TYPE_1__* new_qnode (scalar_t__,int) ; 
 TYPE_1__* parse_query (int) ; 
 TYPE_1__* parse_wordlist (int /*<<< orphan*/ ,scalar_t__,int) ; 
 int /*<<< orphan*/  q_and ; 
 scalar_t__ q_birthday_soon ; 
 scalar_t__ q_false ; 
 scalar_t__ q_true ; 
 char skip_spc () ; 
 int /*<<< orphan*/  strncmp (int /*<<< orphan*/ *,char*,int) ; 
 int strtol (char*,char**,int) ; 

query_t *parse_queryB (int mode) {
  query_t *A, *B;
  int len, value, c;
  struct query_keyword_descr *KW;
  if (skip_spc() == '(') {
    Qs++;
    A = parse_query (mode);
    if (!A) { return A; }
    while (*Qs == ' ' || *Qs == 9) { Qs++; }
    if (*Qs != ')') { return 0; }
    Qs++;
    return A;
  }
  if (*Qs == '!') {
    Qs++;
    A = parse_queryB (mode);
    if (!A) { return 0; }
    A->flags ^= 1;
    return A;
  }
  len = 0;
  if (*Qs >= 'a' && *Qs <= 'z') {
    while (len <= 32 && ((*Qs >= 'a' && *Qs <= 'z') || *Qs == '_' || (*Qs >= '0' && *Qs <= '9'))) {
      len++;
      Qs++;
    }
  }
  if (!len) { return 0; }
  Qs -= len;
  for (KW = QueryKW; KW->q_type; KW++) {
    if ((KW->flags & mode) && !strncmp (KW->str, Qs, len) && !KW->str[len]) {
      break;
    }
  }
  if (!KW->q_type) { return 0; }
  Qs += len;
  skip_spc();
  c = 0;

  if ((KW->flags & 7) == 7) {
    if (Qs[0] != '.') { return 0; }
    Qs++;
    B = parse_queryB (KW->minv);
    if (!B) { return 0; }
    A = new_qnode (KW->q_type, 0);
    if (!A) { return 0; }
    A->left = B;
    A->complexity = B->complexity * 4;
    return A;
  }

  if ((KW->flags & 7) == 6) {
    if (Qs[0] != '.') { return 0; }
    Qs++;
    A = parse_queryB (KW->minv);
    if (!A) { return 0; }
    return A;
  }

  if ((KW->flags & 7) == 3) {
    if (*Qs != '=') { return 0; }
    Qs++;
    skip_spc();
    return parse_wordlist (q_and, KW->q_type, KW->minv);
  }

  if ((KW->flags & 7) == 2) {
    A = new_qnode (KW->q_type, 0);
    if (A->type != q_true && A->type != q_false) {
      A->complexity = 4;
    }
    return A;
  }

  if ((KW->flags & 7) == 1 && (Qs[0] == '>' || Qs[0] == '<') && Qs[1] == '=') {
    c = Qs[0];
    Qs++;
  }

  if (*Qs != '=') { 
    return 0; 
  }
  Qs++;
  skip_spc();

  char *Qs1;
  value = strtol (Qs, &Qs1, 10);
  if (Qs1 == Qs) { 
    return 0; 
  }
  if ((KW->minv != -1 && value < KW->minv) || (KW->maxv != -1 && value > KW->maxv)) { 
    return 0; 
  }
  Qs = Qs1;
  A = new_qnode (KW->q_type, value);
  if (!A) { return 0; }
  if ((KW->flags & 7) == 1) {
    A->flags |= 16;
    A->value2 = value;
    if (c == '<' && (value != KW->minv || value == -1)) { 
      A->value = /* KW->minv */ (KW->minv > 0 ? KW->minv : MININT); 
    }
    if (c == '>' && (value != KW->maxv || value == -1)) { 
      A->value2 = /* KW->maxv */ MAXINT; 
    }
    A->complexity = (A->value == MININT || A->value2 == MAXINT || A->value == A->value2 ? 1 : 2);
  } else {
    A->flags |= 8;
    A->complexity = (A->type == q_birthday_soon ? 4 : 1);
  }
  return A;
}