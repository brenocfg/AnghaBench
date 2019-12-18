#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_4__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  serf_bucket_t ;
struct TYPE_4__ {char* path; } ;
typedef  TYPE_1__ apr_uri_t ;
typedef  scalar_t__ apr_status_t ;
typedef  int /*<<< orphan*/  apr_pool_t ;

/* Variables and functions */
 scalar_t__ APR_SUCCESS ; 
 scalar_t__ apr_uri_parse (int /*<<< orphan*/ *,char const*,TYPE_1__*) ; 
 char* apr_uri_unparse (int /*<<< orphan*/ *,TYPE_1__*,int /*<<< orphan*/ ) ; 
 char* serf_bucket_headers_get (int /*<<< orphan*/ *,char*) ; 
 int /*<<< orphan*/ * serf_bucket_response_get_headers (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  svn_path_is_url (char const*) ; 
 char const* svn_uri_canonicalize (char const*,int /*<<< orphan*/ *) ; 
 scalar_t__ svn_urlpath__canonicalize (char const*,int /*<<< orphan*/ *) ; 

__attribute__((used)) static const char *
response_get_location(serf_bucket_t *response,
                      const char *base_url,
                      apr_pool_t *result_pool,
                      apr_pool_t *scratch_pool)
{
  serf_bucket_t *headers;
  const char *location;

  headers = serf_bucket_response_get_headers(response);
  location = serf_bucket_headers_get(headers, "Location");
  if (location == NULL)
    return NULL;

  /* The RFCs say we should have received a full url in LOCATION, but
     older apache versions and many custom web handlers just return a
     relative path here...

     And we can't trust anything because it is network data.
   */
  if (*location == '/')
    {
      apr_uri_t uri;
      apr_status_t status;

      status = apr_uri_parse(scratch_pool, base_url, &uri);

      if (status != APR_SUCCESS)
        return NULL;

      /* Replace the path path with what we got */
      uri.path = (char*)svn_urlpath__canonicalize(location, scratch_pool);

      /* And make APR produce a proper full url for us */
      location = apr_uri_unparse(scratch_pool, &uri, 0);

      /* Fall through to ensure our canonicalization rules */
    }
  else if (!svn_path_is_url(location))
    {
      return NULL; /* Any other formats we should support? */
    }

  return svn_uri_canonicalize(location, result_pool);
}