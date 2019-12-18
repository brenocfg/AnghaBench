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
typedef  int /*<<< orphan*/  h2o_iovec_t ;

/* Variables and functions */
 unsigned int YOML_TYPE_MAPPING ; 
 unsigned int YOML_TYPE_SCALAR ; 
 unsigned int YOML_TYPE_SEQUENCE ; 
 int /*<<< orphan*/  h2o_fatal (char*,char const*) ; 
 int /*<<< orphan*/  h2o_iovec_init (char const*,int) ; 
 char* strchr (char const*,char) ; 

__attribute__((used)) static const char *get_next_key(const char *start, h2o_iovec_t *output, unsigned *type_mask)
{
    const char *p = strchr(start, ':');
    if (p == NULL)
        goto Error;

    /* set output */
    *output = h2o_iovec_init(start, p - start);

    /* parse attributes */
    *type_mask = 0;
    for (++p; *p != '\0'; ++p) {
        switch (*p) {
        case ',':
            return p + 1;
        case 's':
            *type_mask |= 1u << YOML_TYPE_SCALAR;
            break;
        case 'a':
            *type_mask |= 1u << YOML_TYPE_SEQUENCE;
            break;
        case 'm':
            *type_mask |= 1u << YOML_TYPE_MAPPING;
            break;
        case '*':
            *type_mask |= (1u << YOML_TYPE_SCALAR) | (1u << YOML_TYPE_SEQUENCE) | (1u << YOML_TYPE_MAPPING);
            break;
        default:
            goto Error;
        }
    }

    return NULL;

Error:
    h2o_fatal("detected invalid or missing type specifier; input is: %s\n", start);
}