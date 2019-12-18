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
struct nv {int dummy; } ;
struct hast_resource {int hr_compression; } ;

/* Variables and functions */
#define  HAST_COMPRESSION_HOLE 130 
#define  HAST_COMPRESSION_LZF 129 
#define  HAST_COMPRESSION_NONE 128 
 int /*<<< orphan*/  PJDLOG_ABORT (char*,int) ; 
 int /*<<< orphan*/  compression_name (int) ; 
 scalar_t__ errno ; 
 int /*<<< orphan*/  free (void*) ; 
 unsigned char* hast_hole_compress (void*,size_t*) ; 
 unsigned char* hast_lzf_compress (void*,size_t*) ; 
 int /*<<< orphan*/  nv_add_string (struct nv*,int /*<<< orphan*/ ,char*) ; 
 scalar_t__ nv_error (struct nv*) ; 

int
compression_send(const struct hast_resource *res, struct nv *nv, void **datap,
    size_t *sizep, bool *freedatap)
{
	unsigned char *newbuf;
	int compression;
	size_t size;

	size = *sizep;
	compression = res->hr_compression;

	switch (compression) {
	case HAST_COMPRESSION_NONE:
		return (0);
	case HAST_COMPRESSION_HOLE:
		newbuf = hast_hole_compress(*datap, &size);
		break;
	case HAST_COMPRESSION_LZF:
		/* Try 'hole' compression first. */
		newbuf = hast_hole_compress(*datap, &size);
		if (newbuf != NULL)
			compression = HAST_COMPRESSION_HOLE;
		else
			newbuf = hast_lzf_compress(*datap, &size);
		break;
	default:
		PJDLOG_ABORT("Invalid compression: %d.", res->hr_compression);
	}

	if (newbuf == NULL) {
		/* Unable to compress the data. */
		return (0);
	}
	nv_add_string(nv, compression_name(compression), "compression");
	if (nv_error(nv) != 0) {
		free(newbuf);
		errno = nv_error(nv);
		return (-1);
	}
	if (*freedatap)
		free(*datap);
	*freedatap = true;
	*datap = newbuf;
	*sizep = size;

	return (0);
}