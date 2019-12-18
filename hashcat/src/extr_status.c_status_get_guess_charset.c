#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_2__ ;
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
struct TYPE_4__ {char* custom_charset_1; char* custom_charset_2; char* custom_charset_3; char* custom_charset_4; } ;
typedef  TYPE_1__ user_options_t ;
struct TYPE_5__ {TYPE_1__* user_options; } ;
typedef  TYPE_2__ hashcat_ctx_t ;

/* Variables and functions */
 int /*<<< orphan*/  hc_asprintf (char**,char*,char const*,char const*,char const*,char const*) ; 

char *status_get_guess_charset (const hashcat_ctx_t *hashcat_ctx)
{
  const user_options_t *user_options = hashcat_ctx->user_options;

  const char *custom_charset_1 = user_options->custom_charset_1;
  const char *custom_charset_2 = user_options->custom_charset_2;
  const char *custom_charset_3 = user_options->custom_charset_3;
  const char *custom_charset_4 = user_options->custom_charset_4;

  if ((custom_charset_1 != NULL) || (custom_charset_2 != NULL) || (custom_charset_3 != NULL) || (custom_charset_4 != NULL))
  {
    char *tmp_buf;

    if (custom_charset_1 == NULL) custom_charset_1 = "Undefined";
    if (custom_charset_2 == NULL) custom_charset_2 = "Undefined";
    if (custom_charset_3 == NULL) custom_charset_3 = "Undefined";
    if (custom_charset_4 == NULL) custom_charset_4 = "Undefined";

    hc_asprintf (&tmp_buf, "-1 %s, -2 %s, -3 %s, -4 %s", custom_charset_1, custom_charset_2, custom_charset_3, custom_charset_4);

    return tmp_buf;
  }

  return NULL;
}