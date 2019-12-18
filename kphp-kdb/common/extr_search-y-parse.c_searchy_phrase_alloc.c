#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_2__ ;
typedef  struct TYPE_6__   TYPE_1__ ;

/* Type definitions */
struct TYPE_6__ {TYPE_2__* last_phrase; scalar_t__ words_buf; TYPE_2__** phrases; } ;
typedef  TYPE_1__ searchy_query_t ;
struct TYPE_7__ {int type; scalar_t__ words; scalar_t__ H; struct TYPE_7__* next; } ;
typedef  TYPE_2__ searchy_query_phrase_t ;
typedef  enum searchy_query_phrase_type { ____Placeholder_searchy_query_phrase_type } searchy_query_phrase_type ;

/* Variables and functions */
 int /*<<< orphan*/  assert (int) ; 
 TYPE_2__* zmalloc (int) ; 

__attribute__((used)) static searchy_query_phrase_t *searchy_phrase_alloc (searchy_query_t *Q, enum searchy_query_phrase_type type, int minus) {
  assert (!(minus & -2));
  searchy_query_phrase_t *P = zmalloc (sizeof (*P));
  P->type = type;
  P->words = 0;
  P->next = Q->phrases[minus];
  Q->phrases[minus] = P;
  P->H = Q->last_phrase ? Q->last_phrase->H + Q->last_phrase->words : Q->words_buf;
  return Q->last_phrase = P;
}