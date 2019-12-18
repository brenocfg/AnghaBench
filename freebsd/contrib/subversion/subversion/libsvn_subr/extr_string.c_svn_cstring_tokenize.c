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
 char* apr_strtok (int /*<<< orphan*/ *,char const*,char**) ; 
 char* strchr (char*,char) ; 
 int strlen (char*) ; 

char *
svn_cstring_tokenize(const char *sep, char **str)
{
    char *token;
    char *next;
    char csep;

    /* check parameters */
    if ((sep == NULL) || (str == NULL) || (*str == NULL))
        return NULL;

    /* let APR handle edge cases and multiple separators */
    csep = *sep;
    if (csep == '\0' || sep[1] != '\0')
      return apr_strtok(NULL, sep, str);

    /* skip characters in sep (will terminate at '\0') */
    token = *str;
    while (*token == csep)
        ++token;

    if (!*token)          /* no more tokens */
        return NULL;

    /* skip valid token characters to terminate token and
     * prepare for the next call (will terminate at '\0)
     */
    next = strchr(token, csep);
    if (next == NULL)
      {
        *str = token + strlen(token);
      }
    else
      {
        *next = '\0';
        *str = next + 1;
      }

    return token;
}