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
struct tl_token {char* text; struct tl_token* next; } ;
struct tl_expression {int dummy; } ;
struct tl_compiler {int dummy; } ;

/* Variables and functions */
 void* cstr_dup (char*) ; 
 struct tl_token* list_token_reverse (struct tl_token*) ; 
 int /*<<< orphan*/  strcmp (char*,char*) ; 
 int /*<<< orphan*/  strcpy (char*,char const* const) ; 
 int strlen (char const* const) ; 
 char* strtok (char*,char*) ; 
 scalar_t__ tl_expression_remove_sugar (struct tl_compiler*,struct tl_expression*,char*) ; 
 int /*<<< orphan*/  zfree (char*,int) ; 
 void* zmalloc (int) ; 
 struct tl_token* zmalloc0 (int) ; 

struct tl_token *tl_expresion_split (struct tl_compiler *C, struct tl_expression *E, const char *const expression, int remove_sugar) {
  int l = strlen (expression) + 1;
  char *s = zmalloc (l);
  strcpy (s, expression);

  if (remove_sugar) {
    if (tl_expression_remove_sugar (C, E, s) < 0) {
      return NULL;
    }
  }

  char *p;
  struct tl_token *head = NULL;
  for (p = strtok (s, " "); p != NULL; p = strtok (NULL, " ")) {
    struct tl_token *T = zmalloc0 (sizeof (struct tl_token));

#define ZHUKOV_BYTES_HACK
#ifdef ZHUKOV_BYTES_HACK
    /* dirty hack for Zhukov request */
    if (!strcmp (p, "bytes")) {
      T->text = cstr_dup ("string");
    } else if (!strcmp (p, "Bytes")) {
      T->text = cstr_dup ("String");
    } else {
      int l = strlen (p);
      if (l >= 6 && !strcmp (p + l - 6, ":bytes")) {
        T->text = zmalloc (l + 2);
        strcpy (T->text, p);
        strcpy (T->text + l - 6, ":string");
      } else if (l >= 6 && !strcmp (p + l - 6, ":Bytes")) {
        T->text = zmalloc (l + 2);
        strcpy (T->text, p);
        strcpy (T->text + l - 6, ":String");
      } else {
        T->text = cstr_dup (p);
      }
    }
#else
    T->text = cstr_dup (p);
#endif
    T->next = head;
    head = T;
  }
  zfree (s, l);
  return list_token_reverse (head);
}