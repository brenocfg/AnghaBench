#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_5__   TYPE_1__ ;

/* Type definitions */
typedef  int /*<<< orphan*/  uv_loop_t ;
struct TYPE_5__ {int retcode; int /*<<< orphan*/ * alloc; int /*<<< orphan*/  work_req; struct addrinfoW* addrinfow; int /*<<< orphan*/ * service; int /*<<< orphan*/ * node; int /*<<< orphan*/ * loop; int /*<<< orphan*/ * addrinfo; scalar_t__ getaddrinfo_cb; } ;
typedef  TYPE_1__ uv_getaddrinfo_t ;
typedef  scalar_t__ uv_getaddrinfo_cb ;
struct addrinfoW {int /*<<< orphan*/ * ai_next; int /*<<< orphan*/ * ai_addr; int /*<<< orphan*/ * ai_canonname; scalar_t__ ai_addrlen; int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
struct addrinfo {int /*<<< orphan*/  ai_flags; int /*<<< orphan*/  ai_protocol; int /*<<< orphan*/  ai_socktype; int /*<<< orphan*/  ai_family; } ;
typedef  int /*<<< orphan*/  hostname_ascii ;
typedef  int /*<<< orphan*/  WCHAR ;

/* Variables and functions */
 int ALIGNED_SIZE (int) ; 
 int /*<<< orphan*/  CP_UTF8 ; 
 int GetLastError () ; 
 int MultiByteToWideChar (int /*<<< orphan*/ ,int /*<<< orphan*/ ,char const*,int,int /*<<< orphan*/ *,int) ; 
 int UV_EINVAL ; 
 int /*<<< orphan*/  UV_GETADDRINFO ; 
 int /*<<< orphan*/  UV_REQ_INIT (TYPE_1__*,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  UV__WORK_SLOW_IO ; 
 int WSAENOBUFS ; 
 int strlen (char const*) ; 
 int /*<<< orphan*/  uv__free (int /*<<< orphan*/ *) ; 
 int /*<<< orphan*/  uv__getaddrinfo_done (int /*<<< orphan*/ *,int /*<<< orphan*/ ) ; 
 int /*<<< orphan*/  uv__getaddrinfo_work (int /*<<< orphan*/ *) ; 
 long uv__idna_toascii (char const*,char const*,char*,char*) ; 
 scalar_t__ uv__malloc (int) ; 
 int /*<<< orphan*/  uv__req_register (int /*<<< orphan*/ *,TYPE_1__*) ; 
 int /*<<< orphan*/  uv__work_submit (int /*<<< orphan*/ *,int /*<<< orphan*/ *,int /*<<< orphan*/ ,int /*<<< orphan*/  (*) (int /*<<< orphan*/ *),int /*<<< orphan*/  (*) (int /*<<< orphan*/ *,int /*<<< orphan*/ )) ; 
 int uv_translate_sys_error (int) ; 

int uv_getaddrinfo(uv_loop_t* loop,
                   uv_getaddrinfo_t* req,
                   uv_getaddrinfo_cb getaddrinfo_cb,
                   const char* node,
                   const char* service,
                   const struct addrinfo* hints) {
  char hostname_ascii[256];
  int nodesize = 0;
  int servicesize = 0;
  int hintssize = 0;
  char* alloc_ptr = NULL;
  int err;
  long rc;

  if (req == NULL || (node == NULL && service == NULL)) {
    return UV_EINVAL;
  }

  UV_REQ_INIT(req, UV_GETADDRINFO);
  req->getaddrinfo_cb = getaddrinfo_cb;
  req->addrinfo = NULL;
  req->loop = loop;
  req->retcode = 0;

  /* calculate required memory size for all input values */
  if (node != NULL) {
    rc = uv__idna_toascii(node,
                          node + strlen(node),
                          hostname_ascii,
                          hostname_ascii + sizeof(hostname_ascii));
    if (rc < 0)
      return rc;
    nodesize = ALIGNED_SIZE(MultiByteToWideChar(CP_UTF8, 0, hostname_ascii,
                                                -1, NULL, 0) * sizeof(WCHAR));
    if (nodesize == 0) {
      err = GetLastError();
      goto error;
    }
    node = hostname_ascii;
  }

  if (service != NULL) {
    servicesize = ALIGNED_SIZE(MultiByteToWideChar(CP_UTF8,
                                                   0,
                                                   service,
                                                   -1,
                                                   NULL,
                                                   0) *
                               sizeof(WCHAR));
    if (servicesize == 0) {
      err = GetLastError();
      goto error;
    }
  }
  if (hints != NULL) {
    hintssize = ALIGNED_SIZE(sizeof(struct addrinfoW));
  }

  /* allocate memory for inputs, and partition it as needed */
  alloc_ptr = (char*)uv__malloc(nodesize + servicesize + hintssize);
  if (!alloc_ptr) {
    err = WSAENOBUFS;
    goto error;
  }

  /* save alloc_ptr now so we can free if error */
  req->alloc = (void*)alloc_ptr;

  /* Convert node string to UTF16 into allocated memory and save pointer in the
   * request. */
  if (node != NULL) {
    req->node = (WCHAR*)alloc_ptr;
    if (MultiByteToWideChar(CP_UTF8,
                            0,
                            node,
                            -1,
                            (WCHAR*) alloc_ptr,
                            nodesize / sizeof(WCHAR)) == 0) {
      err = GetLastError();
      goto error;
    }
    alloc_ptr += nodesize;
  } else {
    req->node = NULL;
  }

  /* Convert service string to UTF16 into allocated memory and save pointer in
   * the req. */
  if (service != NULL) {
    req->service = (WCHAR*)alloc_ptr;
    if (MultiByteToWideChar(CP_UTF8,
                            0,
                            service,
                            -1,
                            (WCHAR*) alloc_ptr,
                            servicesize / sizeof(WCHAR)) == 0) {
      err = GetLastError();
      goto error;
    }
    alloc_ptr += servicesize;
  } else {
    req->service = NULL;
  }

  /* copy hints to allocated memory and save pointer in req */
  if (hints != NULL) {
    req->addrinfow = (struct addrinfoW*)alloc_ptr;
    req->addrinfow->ai_family = hints->ai_family;
    req->addrinfow->ai_socktype = hints->ai_socktype;
    req->addrinfow->ai_protocol = hints->ai_protocol;
    req->addrinfow->ai_flags = hints->ai_flags;
    req->addrinfow->ai_addrlen = 0;
    req->addrinfow->ai_canonname = NULL;
    req->addrinfow->ai_addr = NULL;
    req->addrinfow->ai_next = NULL;
  } else {
    req->addrinfow = NULL;
  }

  uv__req_register(loop, req);

  if (getaddrinfo_cb) {
    uv__work_submit(loop,
                    &req->work_req,
                    UV__WORK_SLOW_IO,
                    uv__getaddrinfo_work,
                    uv__getaddrinfo_done);
    return 0;
  } else {
    uv__getaddrinfo_work(&req->work_req);
    uv__getaddrinfo_done(&req->work_req, 0);
    return req->retcode;
  }

error:
  if (req != NULL) {
    uv__free(req->alloc);
    req->alloc = NULL;
  }
  return uv_translate_sys_error(err);
}