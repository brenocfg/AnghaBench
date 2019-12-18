#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_2__   TYPE_1__ ;

/* Type definitions */
struct pem_data {int detached_data; TYPE_1__* os; } ;
typedef  int /*<<< orphan*/  hx509_pem_header ;
typedef  int /*<<< orphan*/  hx509_context ;
struct TYPE_2__ {size_t length; int /*<<< orphan*/ * data; } ;

/* Variables and functions */
 int ENOMEM ; 
 char* hx509_pem_find_header (int /*<<< orphan*/  const*,char*) ; 
 int /*<<< orphan*/ * malloc (size_t) ; 
 int /*<<< orphan*/  memcpy (int /*<<< orphan*/ *,void const*,size_t) ; 
 scalar_t__ strcasecmp (char const*,char*) ; 

__attribute__((used)) static int
pem_reader(hx509_context contextp, const char *type,
	   const hx509_pem_header *headers,
	   const void *data , size_t length, void *ctx)
{
    struct pem_data *p = (struct pem_data *)ctx;
    const char *h;

    p->os->data = malloc(length);
    if (p->os->data == NULL)
	return ENOMEM;
    memcpy(p->os->data, data, length);
    p->os->length = length;

    h = hx509_pem_find_header(headers, "Content-disposition");
    if (h && strcasecmp(h, "detached") == 0)
	p->detached_data = 1;

    return 0;
}