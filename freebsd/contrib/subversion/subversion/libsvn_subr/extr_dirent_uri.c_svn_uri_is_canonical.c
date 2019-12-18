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
typedef  int /*<<< orphan*/  svn_boolean_t ;
typedef  int apr_size_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;
typedef  int apr_int64_t ;

/* Variables and functions */
 int /*<<< orphan*/  FALSE ; 
 int /*<<< orphan*/  TRUE ; 
 scalar_t__ strncmp (char const*,char*,int) ; 
 scalar_t__ strtol (char*,int /*<<< orphan*/ *,int) ; 
 int /*<<< orphan*/  svn_path_is_url (char const*) ; 
 scalar_t__* svn_uri__char_validity ; 

svn_boolean_t
svn_uri_is_canonical(const char *uri, apr_pool_t *scratch_pool)
{
  const char *ptr = uri, *seg = uri;
  const char *schema_data = NULL;

  /* URI is canonical if it has:
   *  - lowercase URL scheme
   *  - lowercase URL hostname
   *  - no '.' segments
   *  - no closing '/'
   *  - no '//'
   *  - uppercase hex-encoded pair digits ("%AB", not "%ab")
   */

  if (*uri == '\0')
    return FALSE;

  if (! svn_path_is_url(uri))
    return FALSE;

  /* Skip the scheme. */
  while (*ptr && (*ptr != '/') && (*ptr != ':'))
    ptr++;

  /* No scheme?  No good. */
  if (! (*ptr == ':' && *(ptr+1) == '/' && *(ptr+2) == '/'))
    return FALSE;

  /* Found a scheme, check that it's all lowercase. */
  ptr = uri;
  while (*ptr != ':')
    {
      if (*ptr >= 'A' && *ptr <= 'Z')
        return FALSE;
      ptr++;
    }
  /* Skip :// */
  ptr += 3;

  /* Scheme only?  That works. */
  if (! *ptr)
    return TRUE;

  /* This might be the hostname */
  seg = ptr;
  while (*ptr && (*ptr != '/') && (*ptr != '@'))
    ptr++;

  if (*ptr == '@')
    seg = ptr + 1;

  /* Found a hostname, check that it's all lowercase. */
  ptr = seg;

  if (*ptr == '[')
    {
      ptr++;
      while (*ptr == ':'
             || (*ptr >= '0' && *ptr <= '9')
             || (*ptr >= 'a' && *ptr <= 'f'))
        {
          ptr++;
        }

      if (*ptr != ']')
        return FALSE;
      ptr++;
    }
  else
    while (*ptr && *ptr != '/' && *ptr != ':')
      {
        if (*ptr >= 'A' && *ptr <= 'Z')
          return FALSE;
        ptr++;
      }

  /* Found a portnumber */
  if (*ptr == ':')
    {
      apr_int64_t port = 0;

      ptr++;
      schema_data = ptr;

      while (*ptr >= '0' && *ptr <= '9')
        {
          port = 10 * port + (*ptr - '0');
          ptr++;
        }

      if (ptr == schema_data && (*ptr == '/' || *ptr == '\0'))
        return FALSE; /* Fail on "http://host:" */

      if (port == 80 && strncmp(uri, "http:", 5) == 0)
        return FALSE;
      else if (port == 443 && strncmp(uri, "https:", 6) == 0)
        return FALSE;
      else if (port == 3690 && strncmp(uri, "svn:", 4) == 0)
        return FALSE;

      while (*ptr && *ptr != '/')
        ++ptr; /* Allow "http://host:stuff" */
    }

  schema_data = ptr;

#ifdef SVN_USE_DOS_PATHS
  if (schema_data && *ptr == '/')
    {
      /* If this is a file url, ptr now points to the third '/' in
         file:///C:/path. Check that if we have such a URL the drive
         letter is in uppercase. */
      if (strncmp(uri, "file:", 5) == 0 &&
          ! (*(ptr+1) >= 'A' && *(ptr+1) <= 'Z') &&
          *(ptr+2) == ':')
        return FALSE;
    }
#endif /* SVN_USE_DOS_PATHS */

  /* Now validate the rest of the URI. */
  seg = ptr;
  while (*ptr && (*ptr != '/'))
    ptr++;
  while(1)
    {
      apr_size_t seglen = ptr - seg;

      if (seglen == 1 && *seg == '.')
        return FALSE;  /*  /./   */

      if (*ptr == '/' && *(ptr+1) == '/')
        return FALSE;  /*  //    */

      if (! *ptr && *(ptr - 1) == '/' && ptr - 1 != uri)
        return FALSE;  /* foo/  */

      if (! *ptr)
        break;

      if (*ptr == '/')
        ptr++;

      seg = ptr;
      while (*ptr && (*ptr != '/'))
        ptr++;
    }

  ptr = schema_data;

  while (*ptr)
    {
      if (*ptr == '%')
        {
          char digitz[3];
          int val;

          /* Can't usesvn_ctype_isxdigit() because lower case letters are
             not in our canonical format */
          if (((*(ptr+1) < '0' || *(ptr+1) > '9'))
              && (*(ptr+1) < 'A' || *(ptr+1) > 'F'))
            return FALSE;
          else if (((*(ptr+2) < '0' || *(ptr+2) > '9'))
                   && (*(ptr+2) < 'A' || *(ptr+2) > 'F'))
            return FALSE;

          digitz[0] = *(++ptr);
          digitz[1] = *(++ptr);
          digitz[2] = '\0';
          val = (int)strtol(digitz, NULL, 16);

          if (svn_uri__char_validity[val])
            return FALSE; /* Should not have been escaped */
        }
      else if (*ptr != '/' && !svn_uri__char_validity[(unsigned char)*ptr])
        return FALSE; /* Character should have been escaped */
      ptr++;
    }

  return TRUE;
}