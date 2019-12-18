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
typedef  scalar_t__ ssize_t ;
struct TYPE_3__ {char* header; char* value; struct TYPE_3__* next; } ;
typedef  TYPE_1__ hx509_pem_header ;
typedef  int /*<<< orphan*/  hx509_context ;
typedef  int /*<<< orphan*/  FILE ;

/* Variables and functions */
 size_t ENCODE_LINE_LENGTH ; 
 int ENOMEM ; 
 scalar_t__ base64_encode (char const*,size_t,char**) ; 
 int /*<<< orphan*/  fprintf (int /*<<< orphan*/ *,char*,char*,...) ; 
 int /*<<< orphan*/  free (char*) ; 
 int /*<<< orphan*/  hx509_set_error_string (int /*<<< orphan*/ ,int /*<<< orphan*/ ,int,char*) ; 
 int /*<<< orphan*/  print_pem_stamp (int /*<<< orphan*/ *,char*,char const*) ; 

int
hx509_pem_write(hx509_context context, const char *type,
		hx509_pem_header *headers, FILE *f,
		const void *data, size_t size)
{
    const char *p = data;
    size_t length;
    char *line;

#define ENCODE_LINE_LENGTH	54

    print_pem_stamp(f, "BEGIN", type);

    while (headers) {
	fprintf(f, "%s: %s\n%s",
		headers->header, headers->value,
		headers->next ? "" : "\n");
	headers = headers->next;
    }

    while (size > 0) {
	ssize_t l;

	length = size;
	if (length > ENCODE_LINE_LENGTH)
	    length = ENCODE_LINE_LENGTH;

	l = base64_encode(p, length, &line);
	if (l < 0) {
	    hx509_set_error_string(context, 0, ENOMEM,
				   "malloc - out of memory");
	    return ENOMEM;
	}
	size -= length;
	fprintf(f, "%s\n", line);
	p += length;
	free(line);
    }

    print_pem_stamp(f, "END", type);

    return 0;
}