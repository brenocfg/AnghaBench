#define NULL ((void*)0)
typedef unsigned long size_t;  // Customize by platform.
typedef long intptr_t; typedef unsigned long uintptr_t;
typedef long scalar_t__;  // Either arithmetic or pointer type.
/* By default, we understand bool (as a convenience). */
typedef int bool;
#define false 0
#define true 1

/* Forward declarations */
typedef  struct TYPE_18__   TYPE_5__ ;
typedef  struct TYPE_17__   TYPE_4__ ;
typedef  struct TYPE_16__   TYPE_3__ ;
typedef  struct TYPE_15__   TYPE_2__ ;
typedef  struct TYPE_14__   TYPE_1__ ;

/* Type definitions */
typedef  scalar_t__ uint32_t ;
typedef  int /*<<< orphan*/  lit_utf8_size_t ;
typedef  int /*<<< orphan*/  lit_utf8_byte_t ;
typedef  scalar_t__ lit_magic_string_ex_id_t ;
struct TYPE_15__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_2__ ecma_utf8_string_t ;
struct TYPE_14__ {scalar_t__ magic_string_ex_id; } ;
struct TYPE_16__ {scalar_t__ refs_and_container; TYPE_1__ u; } ;
typedef  TYPE_3__ ecma_string_t ;
struct TYPE_17__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_4__ ecma_long_utf8_string_t ;
struct TYPE_18__ {int /*<<< orphan*/  size; } ;
typedef  TYPE_5__ ecma_ascii_string_t ;

/* Variables and functions */
 int /*<<< orphan*/  const* ECMA_ASCII_STRING_GET_BUFFER (TYPE_3__ const*) ; 
 scalar_t__ ECMA_DIRECT_STRING_MAGIC ; 
 scalar_t__ ECMA_GET_DIRECT_STRING_TYPE (TYPE_3__ const*) ; 
 int /*<<< orphan*/  ECMA_GET_DIRECT_STRING_VALUE (TYPE_3__ const*) ; 
 scalar_t__ ECMA_IS_DIRECT_STRING (TYPE_3__ const*) ; 
 int /*<<< orphan*/  const* ECMA_LONG_UTF8_STRING_GET_BUFFER (TYPE_3__ const*) ; 
#define  ECMA_STRING_CONTAINER_HEAP_ASCII_STRING 130 
#define  ECMA_STRING_CONTAINER_HEAP_LONG_UTF8_STRING 129 
#define  ECMA_STRING_CONTAINER_HEAP_UTF8_STRING 128 
 int ECMA_STRING_CONTAINER_MAGIC_STRING_EX ; 
 int ECMA_STRING_GET_CONTAINER (TYPE_3__ const*) ; 
 scalar_t__ ECMA_STRING_REF_ONE ; 
 int /*<<< orphan*/  const* ECMA_UTF8_STRING_GET_BUFFER (TYPE_3__ const*) ; 
 int /*<<< orphan*/  JERRY_ASSERT (int) ; 
 scalar_t__ LIT_MAGIC_STRING__COUNT ; 
 int /*<<< orphan*/  lit_get_magic_string_ex_size (scalar_t__) ; 
 int /*<<< orphan*/  const* lit_get_magic_string_ex_utf8 (scalar_t__) ; 
 int /*<<< orphan*/  lit_get_magic_string_size (scalar_t__) ; 
 int /*<<< orphan*/  const* lit_get_magic_string_utf8 (scalar_t__) ; 

__attribute__((used)) static const lit_utf8_byte_t *
ecma_string_get_chars_fast (const ecma_string_t *string_p, /**< ecma-string */
                            lit_utf8_size_t *size_p) /**< [out] size of the ecma string */
{
  if (ECMA_IS_DIRECT_STRING (string_p))
  {
    if (ECMA_GET_DIRECT_STRING_TYPE (string_p) == ECMA_DIRECT_STRING_MAGIC)
    {
      uint32_t id = (uint32_t) ECMA_GET_DIRECT_STRING_VALUE (string_p);

      if (id >= LIT_MAGIC_STRING__COUNT)
      {
        id -= LIT_MAGIC_STRING__COUNT;

        *size_p = lit_get_magic_string_ex_size (id);
        return lit_get_magic_string_ex_utf8 (id);
      }

      *size_p = lit_get_magic_string_size (id);
      return lit_get_magic_string_utf8 (id);
    }
  }

  JERRY_ASSERT (string_p->refs_and_container >= ECMA_STRING_REF_ONE);

  switch (ECMA_STRING_GET_CONTAINER (string_p))
  {
    case ECMA_STRING_CONTAINER_HEAP_UTF8_STRING:
    {
      *size_p = ((ecma_utf8_string_t *) string_p)->size;
      return ECMA_UTF8_STRING_GET_BUFFER (string_p);
    }
    case ECMA_STRING_CONTAINER_HEAP_LONG_UTF8_STRING:
    {
      *size_p = ((ecma_long_utf8_string_t *) string_p)->size;
      return ECMA_LONG_UTF8_STRING_GET_BUFFER (string_p);
    }
    case ECMA_STRING_CONTAINER_HEAP_ASCII_STRING:
    {
      *size_p = ((ecma_ascii_string_t *) string_p)->size;
      return ECMA_ASCII_STRING_GET_BUFFER (string_p);
    }
    default:
    {
      JERRY_ASSERT (ECMA_STRING_GET_CONTAINER (string_p) == ECMA_STRING_CONTAINER_MAGIC_STRING_EX);

      lit_magic_string_ex_id_t id = LIT_MAGIC_STRING__COUNT - string_p->u.magic_string_ex_id;
      *size_p = lit_get_magic_string_ex_size (id);
      return lit_get_magic_string_ex_utf8 (id);
    }
  }
}