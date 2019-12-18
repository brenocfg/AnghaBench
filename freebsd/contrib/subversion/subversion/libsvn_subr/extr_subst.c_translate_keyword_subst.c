#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_3__   TYPE_1__ ;

/* Type definitions */
struct TYPE_3__ {int len; int /*<<< orphan*/  data; } ;
typedef  TYPE_1__ svn_string_t ;
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int apr_size_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int SVN_KEYWORD_MAX_LEN ; 
 int /*<<< orphan*/  TRUE ; 
 int /*<<< orphan*/  assert (int) ; 
 scalar_t__ strncmp (char*,char const*,int) ; 
 int /*<<< orphan*/  strncpy (char*,int /*<<< orphan*/ ,int) ; 

__attribute__((used)) static svn_boolean_t
translate_keyword_subst(char *buf,
                        apr_size_t *len,
                        const char *keyword,
                        apr_size_t keyword_len,
                        const svn_string_t *value)
{
  char *buf_ptr;

  /* Make sure we gotz good stuffs. */
  assert(*len <= SVN_KEYWORD_MAX_LEN);
  assert((buf[0] == '$') && (buf[*len - 1] == '$'));

  /* Need at least a keyword and two $'s. */
  if (*len < keyword_len + 2)
    return FALSE;

  /* Need at least space for two $'s, two spaces and a colon, and that
     leaves zero space for the value itself. */
  if (keyword_len > SVN_KEYWORD_MAX_LEN - 5)
    return FALSE;

  /* The keyword needs to match what we're looking for. */
  if (strncmp(buf + 1, keyword, keyword_len))
    return FALSE;

  buf_ptr = buf + 1 + keyword_len;

  /* Check for fixed-length expansion.
   * The format of fixed length keyword and its data is
   * Unexpanded keyword:         "$keyword::       $"
   * Expanded keyword:           "$keyword:: value $"
   * Expanded kw with filling:   "$keyword:: value   $"
   * Truncated keyword:          "$keyword:: longval#$"
   */
  if ((buf_ptr[0] == ':') /* first char after keyword is ':' */
      && (buf_ptr[1] == ':') /* second char after keyword is ':' */
      && (buf_ptr[2] == ' ') /* third char after keyword is ' ' */
      && ((buf[*len - 2] == ' ')  /* has ' ' for next to last character */
          || (buf[*len - 2] == '#')) /* .. or has '#' for next to last
                                        character */
      && ((6 + keyword_len) < *len))  /* holds "$kw:: x $" at least */
    {
      /* This is fixed length keyword, so *len remains unchanged */
      apr_size_t max_value_len = *len - (6 + keyword_len);

      if (! value)
        {
          /* no value, so unexpand */
          buf_ptr += 2;
          while (*buf_ptr != '$')
            *(buf_ptr++) = ' ';
        }
      else
        {
          if (value->len <= max_value_len)
            { /* replacement not as long as template, pad with spaces */
              strncpy(buf_ptr + 3, value->data, value->len);
              buf_ptr += 3 + value->len;
              while (*buf_ptr != '$')
                *(buf_ptr++) = ' ';
            }
          else
            {
              /* replacement needs truncating */
              strncpy(buf_ptr + 3, value->data, max_value_len);
              buf[*len - 2] = '#';
              buf[*len - 1] = '$';
            }
        }
      return TRUE;
    }

  /* Check for unexpanded keyword. */
  else if (buf_ptr[0] == '$')          /* "$keyword$" */
    {
      /* unexpanded... */
      if (value)
        {
          /* ...so expand. */
          buf_ptr[0] = ':';
          buf_ptr[1] = ' ';
          if (value->len)
            {
              apr_size_t vallen = value->len;

              /* "$keyword: value $" */
              if (vallen > (SVN_KEYWORD_MAX_LEN - 5 - keyword_len))
                vallen = SVN_KEYWORD_MAX_LEN - 5 - keyword_len;
              strncpy(buf_ptr + 2, value->data, vallen);
              buf_ptr[2 + vallen] = ' ';
              buf_ptr[2 + vallen + 1] = '$';
              *len = 5 + keyword_len + vallen;
            }
          else
            {
              /* "$keyword: $"  */
              buf_ptr[2] = '$';
              *len = 4 + keyword_len;
            }
        }
      else
        {
          /* ...but do nothing. */
        }
      return TRUE;
    }

  /* Check for expanded keyword. */
  else if (((*len >= 4 + keyword_len ) /* holds at least "$keyword: $" */
           && (buf_ptr[0] == ':')      /* first char after keyword is ':' */
           && (buf_ptr[1] == ' ')      /* second char after keyword is ' ' */
           && (buf[*len - 2] == ' '))
        || ((*len >= 3 + keyword_len ) /* holds at least "$keyword:$" */
           && (buf_ptr[0] == ':')      /* first char after keyword is ':' */
           && (buf_ptr[1] == '$')))    /* second char after keyword is '$' */
    {
      /* expanded... */
      if (! value)
        {
          /* ...so unexpand. */
          buf_ptr[0] = '$';
          *len = 2 + keyword_len;
        }
      else
        {
          /* ...so re-expand. */
          buf_ptr[0] = ':';
          buf_ptr[1] = ' ';
          if (value->len)
            {
              apr_size_t vallen = value->len;

              /* "$keyword: value $" */
              if (vallen > (SVN_KEYWORD_MAX_LEN - 5 - keyword_len))
                vallen = SVN_KEYWORD_MAX_LEN - 5 - keyword_len;
              strncpy(buf_ptr + 2, value->data, vallen);
              buf_ptr[2 + vallen] = ' ';
              buf_ptr[2 + vallen + 1] = '$';
              *len = 5 + keyword_len + vallen;
            }
          else
            {
              /* "$keyword: $"  */
              buf_ptr[2] = '$';
              *len = 4 + keyword_len;
            }
        }
      return TRUE;
    }

  return FALSE;
}