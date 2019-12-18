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
struct passwd {char const* pw_dir; } ;

/* Variables and functions */
 int /*<<< orphan*/  ID0realuid () ; 
 int LINE_LEN ; 
 int /*<<< orphan*/  endpwent () ; 
 char* getenv (char*) ; 
 struct passwd* getpwnam (char*) ; 
 struct passwd* getpwuid (int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  isalnum (char const) ; 
 scalar_t__ issep (char const) ; 
 char* strchr (char const*,char) ; 
 size_t strlen (char const*) ; 
 int /*<<< orphan*/  strncpy (char*,char const*,int) ; 

const char *
InterpretArg(const char *from, char *to)
{
  char *ptr, *startto, *endto;
  struct passwd *pwd;
  int instring;
  size_t len;
  const char *env;

  instring = 0;
  startto = to;
  endto = to + LINE_LEN - 1;

  while(issep(*from))
    from++;

  while (*from != '\0') {
    switch (*from) {
      case '"':
        instring = !instring;
        *to++ = *from++;
        break;
      case '\\':
        switch (*++from) {
          case '$':
          case '~':
            break;		/* Swallow the escapes */

          default:
            *to++ = '\\';	/* Pass the escapes on, maybe skipping \# */
            break;
        }
        *to++ = *from++;
        break;
      case '$':
        if (from[1] == '$') {
          *to = '\0';	/* For an empty var name below */
          from += 2;
        } else if (from[1] == '{') {
          ptr = strchr(from+2, '}');
          if (ptr) {
            len = ptr - from - 2;
            if (endto - to < (int)len )
              len = endto - to;
            if (len) {
              strncpy(to, from+2, len);
              to[len] = '\0';
              from = ptr+1;
            } else {
              *to++ = *from++;
              continue;
            }
          } else {
            *to++ = *from++;
            continue;
          }
        } else {
          ptr = to;
          for (from++; (isalnum(*from) || *from == '_') && ptr < endto; from++)
            *ptr++ = *from;
          *ptr = '\0';
        }
        if (*to == '\0')
          *to++ = '$';
        else if ((env = getenv(to)) != NULL) {
          strncpy(to, env, endto - to);
          *endto = '\0';
          to += strlen(to);
        }
        break;

      case '~':
        ptr = strchr(++from, '/');
        len = ptr ? (size_t)(ptr - from) : strlen(from);
        if (len == 0)
          pwd = getpwuid(ID0realuid());
        else {
          strncpy(to, from, len);
          to[len] = '\0';
          pwd = getpwnam(to);
        }
        if (pwd == NULL)
          *to++ = '~';
        else {
          strncpy(to, pwd->pw_dir, endto - to);
          *endto = '\0';
          to += strlen(to);
          from += len;
        }
        endpwent();
        break;

      default:
        *to++ = *from++;
        break;
    }
  }

  while (to > startto) {
    to--;
    if (!issep(*to)) {
      to++;
      break;
    }
  }
  *to = '\0';

  return from;
}