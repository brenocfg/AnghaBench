#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_7__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ gssize ;
typedef  int gsize ;
typedef  int /*<<< orphan*/  gchar ;
struct TYPE_7__ {int /*<<< orphan*/  const* str; } ;
typedef  TYPE_1__ GString ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  g_assert (scalar_t__) ; 
 int /*<<< orphan*/  g_return_val_if_fail (int /*<<< orphan*/ ,int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  g_string_append (TYPE_1__*,char*) ; 
 int /*<<< orphan*/  g_string_append_c (TYPE_1__*,char) ; 
 int /*<<< orphan*/  g_string_append_len (TYPE_1__*,int /*<<< orphan*/  const*,int) ; 
 int /*<<< orphan*/ * g_string_free (TYPE_1__*,int /*<<< orphan*/ ) ; 
 TYPE_1__* g_string_sized_new (int) ; 
 int /*<<< orphan*/ * g_strndup (int /*<<< orphan*/  const*,scalar_t__) ; 
 scalar_t__ g_utf8_validate (int /*<<< orphan*/  const*,int,int /*<<< orphan*/  const**) ; 
 scalar_t__ strlen (int /*<<< orphan*/  const*) ; 

gchar *
g_utf8_make_valid (const gchar *str,
                   gssize       len)
{
  GString *string;
  const gchar *remainder, *invalid;
  gsize remaining_bytes, valid_bytes;

  g_return_val_if_fail (str != NULL, NULL);

  if (len < 0)
    len = strlen (str);

  string = NULL;
  remainder = str;
  remaining_bytes = len;

  while (remaining_bytes != 0)
    {
      if (g_utf8_validate (remainder, remaining_bytes, &invalid))
	break;
      valid_bytes = invalid - remainder;

      if (string == NULL)
	string = g_string_sized_new (remaining_bytes);

      g_string_append_len (string, remainder, valid_bytes);
      /* append U+FFFD REPLACEMENT CHARACTER */
      g_string_append (string, "\357\277\275");

      remaining_bytes -= valid_bytes + 1;
      remainder = invalid + 1;
    }

  if (string == NULL)
    return g_strndup (str, len);

  g_string_append_len (string, remainder, remaining_bytes);
  g_string_append_c (string, '\0');

  g_assert (g_utf8_validate (string->str, -1, NULL));

  return g_string_free (string, FALSE);
}